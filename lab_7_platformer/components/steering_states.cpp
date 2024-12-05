#include "steering_states.h"
#include "cmp_sprite.h"

using namespace sf;

//TEST - if in stationary state then colour blue
void StationaryState::execute(Entity* owner, double dt) noexcept {
    auto s = owner->get_components<ShapeComponent>();
    s[0]->getShape().setFillColor(Color::Blue);
}

//TEST - if in seek state then colour green
void SeekState::execute(Entity* owner, double dt) noexcept {
    auto s = owner->get_components<ShapeComponent>();
    s[0]->getShape().setFillColor(Color::Green);
    auto output = _steering.getSteering();
    owner->setPosition(owner->getPosition() + (output.direction * (float)dt));
}

//TEST - if in flee state then colour red
void FleeState::execute(Entity* owner, double dt) noexcept {
    auto s = owner->get_components<ShapeComponent>();
    s[0]->getShape().setFillColor(Color::Red);
    auto output = _steering.getSteering();
    owner->setPosition(owner->getPosition() + (output.direction * (float)dt));
}