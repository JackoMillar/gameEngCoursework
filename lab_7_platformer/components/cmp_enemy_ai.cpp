#include "cmp_enemy_ai.h"

using namespace std;
using namespace sf;

//steeringComponent will control the AI movement 
//key beaviour is here in update
void SteeringComponent::update(double dt) {
    // If target (player) is more than 100 pixels away then seek
    if (length(_parent->getPosition() - _player->getPosition()) > 100.0f) {
        auto output = _seek.getSteering();
        move(output.direction * (float)dt);
    }
    
    // If target (player) is less than 50 pixels away then flee
    else if (length(_parent->getPosition() - _player->getPosition()) <
        50.0f) {
        auto output = _flee.getSteering();
        move(output.direction * (float)dt);
    }
    
}

SteeringComponent::SteeringComponent(Entity* p, Entity* player)
    : _player(player), _seek(Seek(p, player, 100.0f)),
   _flee(Flee(p, player, 100.0f)),  Component(p) {}

bool SteeringComponent::validMove(const sf::Vector2f& pos) const {
    if (pos.x < 0.0f || pos.x > Engine::GetWindow().getSize().x ||
        pos.y < 0.0f || pos.y > Engine::GetWindow().getSize().y) {
        return false;
    }
    return true;
}

void SteeringComponent::move(const sf::Vector2f& p) {
    auto new_pos = _parent->getPosition() + p;
    if (validMove(new_pos)) {
        _parent->setPosition(new_pos);
    }
}

void SteeringComponent::move(float x, float y) { move(Vector2f(x, y)); }


//probably not using but keeping for now
/*
void EnemyAIComponent::update(double dt) {
  auto mov = _direction * (float)(dt * _speed);
  mov.x += _direction.x * 16.f;
  if (!validMove(_parent->getPosition() + mov)) {
    _direction *= -1.f;
  }

  move(_direction * (float)(dt * _speed));
  ActorMovementComponent::update(dt);
}

EnemyAIComponent::EnemyAIComponent(Entity* p) : ActorMovementComponent(p) {
  _direction = Vector2f(1.0f, 0);
  _speed = 100.0f;
}
*/