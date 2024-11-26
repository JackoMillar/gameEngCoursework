#pragma once

#include "cmp_actor_movement.h"
//using this as the StateMachineComponent - if using states

class EnemyAIComponent : public ActorMovementComponent {
protected:
  sf::Vector2f _direction;
 //enum state {ROAMING, ROTATING, ROTATED};
//state _state;
/*
//SEEK, ARRIVE, FACE,
ARRIVE - Move towards target and stop when within a given distance
So ARRIVE for triangle, SEEK and maybe FACE for square
*/

public:
  void update(double dt) override;

  explicit EnemyAIComponent(Entity* p);

  EnemyAIComponent() = delete;
};
