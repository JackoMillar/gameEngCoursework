#include "cmp_state_machine.h"
#include "steering_decisions.h"

using namespace std;

StateMachineComponent::StateMachineComponent(Entity* p) :
_current_state(nullptr), Component(p) { }

//executing current state
void StateMachineComponent::update(double dt)
{
    if (_current_state != nullptr) {
        _current_state->execute(_parent, dt);
    }
}

//adding a state method
void StateMachineComponent::addState(const string& name, shared_ptr<State> state) noexcept
{
    _states[name] = state;
}

//getting state method
shared_ptr<State> StateMachineComponent::getState(const string& name) const noexcept
{
    auto found = _states.find(name);
    if (found != _states.end()) {
        return found->second;
    }
    else {
        return nullptr;
    }
}

//removing state method
void StateMachineComponent::removeState(const string& name) noexcept
{
    _states.erase(name);
}

//changing state method
void StateMachineComponent::changeState(const string& name) noexcept
{
    auto found = _states.find(name);
    if (found != _states.end()) {
        _current_state = found->second;
        _current_state_name = name;
    }
}