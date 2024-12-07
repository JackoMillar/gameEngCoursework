//cmp_steering.h
#pragma once
#include <engine.h>

struct SteeringOutput
{
    //allow us to move or rotate
    //basics of the steering behaviour
    //Direction of travel.
    sf::Vector2f direction;

    //Rotation of travel.
    float rotation;
};

// Base class for steering behaviour
class SteeringBehaviour {
public:
    virtual ~SteeringBehaviour() = default;

    // Gets the output from a steering behaviour;
    virtual SteeringOutput getSteering() const noexcept = 0;
};

//creating the steering behaviours

//Seek steering behaviour
//moves an object to a target
class Seek : public SteeringBehaviour {
private:
    Entity* _character;
    Entity* _target;
    float _maxSpeed;
public:
    Seek() = delete;
    Seek(Entity* character, Entity* target, float maxSpeed)
        : _character(character), _target(target), _maxSpeed(maxSpeed) { }
    SteeringOutput getSteering() const noexcept;
};

//Flee steering behaviour
//moves an object away from a target

class Flee : public SteeringBehaviour {
private:
    Entity* _character;
    Entity* _target;
    float _maxSpeed;
public:
    Flee() = delete;
    Flee(Entity* character, Entity* target, float maxSpeed)
        : _character(character), _target(target), _maxSpeed(maxSpeed) { }
    SteeringOutput getSteering() const noexcept;
};
