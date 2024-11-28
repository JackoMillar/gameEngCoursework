#include "cmp_steering.h"

using namespace sf;

//seek behaviour
SteeringOutput Seek::getSteering() const noexcept {
    SteeringOutput steering;
    steering.direction = _target->getPosition() - _character->getPosition();
    steering.direction = normalize(steering.direction);
    steering.direction *= _maxSpeed;
    steering.rotation = 0.0f;
    return steering;
}


//flee behaviour
SteeringOutput Flee::getSteering() const noexcept {
    SteeringOutput steering;
    steering.direction = _character->getPosition() - _target->getPosition();
    steering.direction = normalize(steering.direction);
    steering.direction *= _maxSpeed;
    steering.rotation = 0.0f;
    return steering;
}