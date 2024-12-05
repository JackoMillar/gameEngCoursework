#include "cmp_enemy_states.h"
#include "cmp_sprite.h"

using namespace sf;

//if player is far away set colour to blue
void NormalState::execute(Entity* owner, double dt) noexcept {
    auto s = owner->get_components<ShapeComponent>();
    s[0]->getShape().setFillColor(Color::Yellow);

    //check if need to change state
    if (length(owner->getPosition() - _player->getPosition()) < 100.0f) {
        auto sm = owner->get_components<StateMachineComponent>();
        sm[0]->changeState("near");
    }
}

//if player is near, colour is set to green
void NearState::execute(Entity* owner, double dt) noexcept {
    auto s = owner->get_components<ShapeComponent>();
    s[0]->getShape().setFillColor(Color::Green);

    //check if need to change state
    if (length(owner->getPosition() - _player->getPosition()) > 100.0f) {
        auto sm = owner->get_components<StateMachineComponent>();
        sm[0]->changeState("normal");
    }
}