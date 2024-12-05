//steering_states.h
#pragma once

#include "cmp_steering.h"
#include "cmp_state_machine.h"
#include "cmp_physics.h"

class StationaryState : public State
{
public:
    StationaryState() = default;
    void execute(Entity*, double) noexcept override;
};

//calling Seek behaviour
class SeekState : public State
{
private:
    Seek _steering;
public:
    SeekState(std::shared_ptr<Entity> owner, std::shared_ptr<Entity> player) : 
    _steering(owner.get(), player.get(), 50.0f) { }
    void execute(Entity*, double) noexcept override;
};

//calling Flee behaviour
class FleeState : public State
{
private:
    Flee _steering;
public:
    FleeState(std::shared_ptr<Entity> owner, std::shared_ptr<Entity> player) : 
    _steering(owner.get(), player.get(), 50.0f) { }
    void execute(Entity*, double) noexcept override;
};