#pragma once
#include <ecm.h>
#include "cmp_steering.h"
//#include "cmp_actor_movement.h"


//steeringComponent will control the AI movement
class SteeringComponent : public Component {
protected:
    Seek _seek;
    Flee _flee;
    Entity* _player;
    bool validMove(const sf::Vector2f&) const;
public:
    void update(double) override;
    void move(const sf::Vector2f&);
    void move(float x, float y);
    void render() override { }
    explicit SteeringComponent(Entity* p, Entity* player);
    SteeringComponent() = delete;
};


/*
class EnemyAIComponent : public ActorMovementComponent {
protected:
  sf::Vector2f _direction;

public:
  void update(double dt) override;

  explicit EnemyAIComponent(Entity* p);

  EnemyAIComponent() = delete;
};
*/