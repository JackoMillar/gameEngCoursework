#include "cmp_player_physics.h"
#include "system_physics.h"
#include "cmp_player_abilities.h"
#include "../components/cmp_scoring.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>

using namespace std;
using namespace sf;
using namespace Physics;

bool doubleJump = false;

/*
    Check if Player is touching the ground.    
*/
bool PlayerPhysicsComponent::isGrounded() const {
    auto touch = getTouching();
    const auto& pos = _body->GetPosition();
    const float halfPlrHeigt = _size.y * .5f;
    const float halfPlrWidth = _size.x * .52f;
    b2WorldManifold manifold;
    for (const auto& contact : touch) {
        contact->GetWorldManifold(&manifold);
        const int numPoints = contact->GetManifold()->pointCount;
        bool onTop = numPoints > 0;
        // If all contacts are below the player.
        for (int j = 0; j < numPoints; j++) {
            onTop &= (manifold.points[j].y < pos.y - halfPlrHeigt);
        }
        if (onTop) {
            return true;
        }
    }
    return false;
}

/*
    Check if the player is touching a roof
*/
bool PlayerPhysicsComponent::isRoofed() const {
    auto touch = getTouching();
    const auto& pos = _body->GetPosition();
    const float halfPlrHeight = _size.y * 0.5f;
    b2WorldManifold manifold;

    for (const auto& contact : touch) {
        contact->GetWorldManifold(&manifold);
        const int numPoints = contact->GetManifold()->pointCount;
        bool onBottom = numPoints > 0;

        // If all contact points are above the player.
        for (int j = 0; j < numPoints; j++) {
            onBottom &= (manifold.points[j].y > pos.y + halfPlrHeight);
        }

        if (onBottom) {
            return true;
        }
    }

    return false;
}

/*
    Check if the player is touching the wall
*/
bool PlayerPhysicsComponent::isWalled() const {
    auto touch = getTouching();
    const auto& pos = _body->GetPosition();
    const float halfPlrHeight = _size.y * 0.5f;
    const float halfPlrWidth = _size.x * 0.52f; 
    b2WorldManifold manifold;

    for (const auto& contact : touch) {
        contact->GetWorldManifold(&manifold);
        const int numPoints = contact->GetManifold()->pointCount;
        bool onSide = numPoints > 0;

        // Check if any contact points are to the left or right of the player.
        for (int j = 0; j < numPoints; j++) {
            // Check if point is to the left or right of player's width boundary
            bool isLeft = (manifold.points[j].x < pos.x - halfPlrWidth);
            bool isRight = (manifold.points[j].x > pos.x + halfPlrWidth);

            if (isLeft || isRight) {
                return true;  // Wall detected on either side
            }
        }
    }
    return false;
}

void PlayerPhysicsComponent::update(double dt) {

    const auto pos = _parent->getPosition();

    //checks to see where the player is at
    _grounded = isGrounded();
    _walled = isWalled();
    _roofed = isRoofed();

    // Collision with roof/wall/ground
    if (_grounded || _walled || _roofed || doubleJump) {

        // Ground Jump
        if (_grounded || doubleJump) {

            // When the ball hits the ground
            if (_grounded)
            {
                doubleJump = true;
                setVelocity(Vector2f(getVelocity().x, getVelocity().y));

                // teleport ball away from the ground and impulse it upwards
                teleport(Vector2f(pos.x, pos.y - 5.0f));
                impulse(Vector2f(0, -10.f));
                printf("GROUND\n");

                // Add score when the player hits the ground
                auto scoreComponent = _parent->GetCompatibleComponent<ScoreComponent>();
                if (!scoreComponent.empty()) {
                    scoreComponent[0]->addScore(10);
                }
            }

            // if player wants to jump upwards from ground or double jump upwards
            if ((Keyboard::isKeyPressed(Keyboard::Up) && _grounded) ||
                (Keyboard::isKeyPressed(Keyboard::Up) &&
                Keyboard::isKeyPressed(Keyboard::Space) &&
                doubleJump == true)) {

                teleport(Vector2f(pos.x, pos.y - 2.0f));
                impulse(Vector2f(0, -4.f));
                printf("UP\n");

                // deactivate double jump
                if (Keyboard::isKeyPressed(Keyboard::Space) && doubleJump)
                {
                    doubleJump = false;
                    impulse(Vector2f(0, -4.f));
                    printf("DOUBLE-JUMP\n");
                    if (getVelocity().y <= 0) {
                        setVelocity(Vector2f(getVelocity().x, 0.f));
                        impulse(Vector2f(0, -2.f));
                    }
                }
            }
            // if player wants to jump lower or double jump downwards
            if ((Keyboard::isKeyPressed(Keyboard::Down) && _grounded) ||
                (Keyboard::isKeyPressed(Keyboard::Down) &&
                Keyboard::isKeyPressed(Keyboard::Space) &&
                doubleJump == true)) {
                teleport(Vector2f(pos.x, pos.y - 2.0f));
                impulse(Vector2f(0, 4.f));
                printf("DOWN\n");

                // deactivate double jump
                if (Keyboard::isKeyPressed(Keyboard::Space) && doubleJump)
                {
                    doubleJump = false;
                    printf("DOUBLE-JUMP\n");
                }
            }
        }
        if (_walled) {
            if (getVelocity().x < 0) {
                setVelocity(Vector2f(getVelocity().x * 0.9f, getVelocity().y));
                teleport(Vector2f(pos.x - 10.0f, pos.y));
                impulse(Vector2f(-3.f, 0));
                printf("RIGHTWALL\n");
            }
            else
            {
                setVelocity(Vector2f(getVelocity().x * 0.9f, getVelocity().y));
                teleport(Vector2f(pos.x + 10.0f, pos.y));
                impulse(Vector2f(3.f, 0));
                printf("LEFTWALL\n");
            }
           
        }
        if (_roofed) {
            setVelocity(Vector2f(getVelocity().x, getVelocity().y));
            teleport(Vector2f(pos.x, pos.y + 10.0f));
            printf("ROOF\n");
        }
    }

    // Left/Right Jumps
    if ((Keyboard::isKeyPressed(Keyboard::Left) ||
        Keyboard::isKeyPressed(Keyboard::Right))
        && _grounded || doubleJump) {

        if ((((Keyboard::isKeyPressed(Keyboard::Right) && _grounded) ||
            (Keyboard::isKeyPressed(Keyboard::Right) &&
             Keyboard::isKeyPressed(Keyboard::Space) &&
             doubleJump == true))) && !(Keyboard::isKeyPressed(Keyboard::Left))) {
            if (getVelocity().x < 0)
            {
                setVelocity(Vector2f(0, getVelocity().y));
                printf("DAMPRIGHT");
            }
                
            setVelocity(Vector2f(getVelocity().x, getVelocity().y));
            teleport(Vector2f(pos.x, pos.y - 5.0f));
            impulse(Vector2f(10.f, 0));  // Positive X impulse for moving right
            printf("RIGHT\n");

            if (Keyboard::isKeyPressed(Keyboard::Up)) {

                impulse(Vector2f(0, +3.f));
                printf("LESS-UP\n");
            }

            if (Keyboard::isKeyPressed(Keyboard::Space) && doubleJump)
            {
                doubleJump = false;
                printf("DOUBLE-JUMP\n");
            }
            
        }
        if ((((Keyboard::isKeyPressed(Keyboard::Left) && _grounded) ||
            (Keyboard::isKeyPressed(Keyboard::Left) &&
            Keyboard::isKeyPressed(Keyboard::Space) &&
            doubleJump == true))) && !(Keyboard::isKeyPressed(Keyboard::Right))) {
            if (getVelocity().x > 0)
            {
                setVelocity(Vector2f(0, getVelocity().y));
                printf("DAMPLEFT");
            }
               
                // Apply horizontal impulse to the left direction
                setVelocity(Vector2f(getVelocity().x, getVelocity().y));
                teleport(Vector2f(pos.x, pos.y - 5.0f));
                impulse(Vector2f(-10.f, 0));  // Negative X impulse for moving left
                printf("LEFT\n");

                if (Keyboard::isKeyPressed(Keyboard::Up)) {

                    impulse(Vector2f(0, +3.f));
                    printf("LESS-UP\n");
                }

            if (Keyboard::isKeyPressed(Keyboard::Space) && doubleJump)
            {
                doubleJump = false;
                printf("DOUBLE-JUMP\n");
            }

            
        }

    }    

    //Are we in air?
    if (!_grounded) {
        // Check to see if we have landed yet
        _grounded = isGrounded();
        // disable friction while jumping
        setFriction(0.f);
    }
    else {
        setFriction(0.1f);
    }

    PhysicsComponent::update(dt);
}

PlayerPhysicsComponent::PlayerPhysicsComponent(Entity* p,
    const Vector2f& size)
    : PhysicsComponent(p, true, size) {
    _size = sv2_to_bv2(size, true);
    _maxVelocity = Vector2f(200.f, 400.f);
    _groundspeed = 40.f;
    _grounded = false;
    _body->SetSleepingAllowed(false);
    _body->SetFixedRotation(true);
    //Bullet items have higher-res collision detection
    _body->SetBullet(true);
}