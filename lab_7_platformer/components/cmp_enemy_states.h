//enemy_states.h

#include "cmp_state_machine.h"

//normal state when player is far from enemy view
class NormalState : public State
{
private:
    std::shared_ptr<Entity> _player;
public:
    NormalState(std::shared_ptr<Entity> player) : _player(player) { }
    void execute(Entity*, double) noexcept override;
};

//near state for when the player is within set distance
class NearState : public State
{
private:
    std::shared_ptr<Entity> _player;
public:
    NearState(std::shared_ptr<Entity> player) : _player(player) { }
    void execute(Entity*, double) noexcept override;
};