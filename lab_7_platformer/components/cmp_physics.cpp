#include "cmp_physics.h"
#include "system_physics.h"

using namespace std;
using namespace sf;

using namespace Physics;

void PhysicsComponent::update(double dt) {
  _parent->setPosition(invert_height(bv2_to_sv2(_body->GetPosition())));
  _parent->setRotation((180 / b2_pi) * _body->GetAngle());
}

PhysicsComponent::PhysicsComponent(Entity* p, bool dyn,
                                   const Vector2f& size)
    : Component(p), _dynamic(dyn) {

  b2BodyDef BodyDef;
  const float physics_scale = 25.0f;
  // Is Dynamic(moving), or static(Stationary)
  BodyDef.type = _dynamic ? b2_dynamicBody : b2_staticBody;
  BodyDef.position = sv2_to_bv2(invert_height(p->getPosition()));

  // Create the body
  _body = Physics::GetWorld()->CreateBody(&BodyDef);
  _body->SetActive(true);
  {
    // Create the fixture shape
    b2CircleShape Shape;
    // SetAsBox box takes HALF-Widths!
    Shape.m_radius = (size.x * 0.5f) / physics_scale;
    b2FixtureDef FixtureDef;
    // Fixture properties
    // FixtureDef.density = _dynamic ? 10.f : 0.f;
    FixtureDef.friction = _dynamic ? 0.1f : 0.8f;
    FixtureDef.restitution = .2;
    FixtureDef.shape = &Shape;
    // Add to body
    _fixture = _body->CreateFixture(&FixtureDef);
    //_fixture->SetRestitution(.9)
    FixtureDef.restitution = .2;
  }

  // An ideal Pod/capusle shape should be used for hte player,
  // this isn't built into B2d, but we can combine two shapes to do so.
  // This would allwo the player to go up steps
  /*
    BodyDef.bullet = true;
    b2PolygonShape shape1;
    shape1.SetAsBox(sv2_to_bv2(size).x * 0.5f, sv2_to_bv2(size).y * 0.5f);
    {
      b2PolygonShape poly ;
      poly.SetAsBox(0.45f, 1.4f);
      b2FixtureDef FixtureDefPoly;

      FixtureDefPoly.shape = &poly;
      _body->CreateFixture(&FixtureDefPoly);

    }
    {
      b2CircleShape circle;
      circle.m_radius = 0.45f;
      circle.m_p.Set(0, -1.4f);
      b2FixtureDef FixtureDefCircle;
      FixtureDefCircle.shape = &circle;
      _body->CreateFixture(&FixtureDefCircle);
    }
  */
}

void PhysicsComponent::setFriction(float r) { _fixture->SetFriction(r); }

void PhysicsComponent::setMass(float m) {
  _fixture->SetDensity(m);
  _body->ResetMassData();
}

void PhysicsComponent::teleport(const sf::Vector2f& v) {
  _body->SetTransform(sv2_to_bv2(invert_height(v)), 0.0f);
}

const sf::Vector2f PhysicsComponent::getVelocity() const {
  return bv2_to_sv2(_body->GetLinearVelocity(), true);
}
void PhysicsComponent::setVelocity(const sf::Vector2f& v) {
  _body->SetLinearVelocity(sv2_to_bv2(v, true));
}

b2Fixture* const PhysicsComponent::getFixture() const { return _fixture; }

PhysicsComponent::~PhysicsComponent() {
  auto a = Physics::GetWorld();
  _body->SetActive(false);
  Physics::GetWorld()->DestroyBody(_body);
  // delete _body;
  _body = nullptr;
}

void PhysicsComponent::setWeightless(){
  _body->SetGravityScale(0);
}

void PhysicsComponent::render() {}

void PhysicsComponent::impulse(const sf::Vector2f& i) {
  auto a = b2Vec2(i.x, i.y * -1.0f);
  _body->ApplyLinearImpulseToCenter(a, true);
}

void PhysicsComponent::dampen(const sf::Vector2f& i) {
  auto vel = _body->GetLinearVelocity();
  vel.x *= i.x;
  vel.y *= i.y;
  _body->SetLinearVelocity(vel);
}

bool PhysicsComponent::isTouching(const PhysicsComponent& pc) const {
    const b2Fixture* otherFixture = pc.getFixture();

    // Traverse all contact edges
    b2ContactEdge* edge = _body->GetContactList();
    while (edge != nullptr) {
        b2Contact* contact = edge->contact;

        // Check if the contact involves our fixture and the other fixture
        if (contact->IsTouching() &&
            ((contact->GetFixtureA() == _fixture && contact->GetFixtureB() == otherFixture) ||
                (contact->GetFixtureA() == otherFixture && contact->GetFixtureB() == _fixture))) {
            return true;
        }
        edge = edge->next;
    }

    return false;
}

bool PhysicsComponent::isTouching(const PhysicsComponent& pc, const b2Contact*& bc) const {
  const b2Fixture* otherFixture = pc.getFixture();

  b2ContactEdge* edge = _body->GetContactList();
  while (edge != nullptr) {
    b2Contact* contact = edge->contact;

    if (contact->IsTouching() &&
        ((contact->GetFixtureA() == _fixture && contact->GetFixtureB() == otherFixture) ||
         (contact->GetFixtureA() == otherFixture && contact->GetFixtureB() == _fixture))) {
      bc = contact; // Set the contact reference
      return true;
    }
    edge = edge->next;
  }

  bc = nullptr; // Ensure bc is set to null if no contact is found
  return false;
}

std::vector<const b2Contact const*> PhysicsComponent::getTouching() const {
  std::vector<const b2Contact const*> ret;

  b2ContactEdge* edge = _body->GetContactList();
  while (edge != NULL) {
    const b2Contact* contact = edge->contact;
    if (contact->IsTouching()) {
      ret.push_back(contact);
    }
    edge = edge->next;
  }

  return ret;
}

void PhysicsComponent::setRestitution(float r) {
  _fixture->SetRestitution(r);
}
