//cmp_state_machine.h
#pragma once

#include <ecm.h>
#include <unordered_map>
#include <string>

class State {
public:
	virtual ~State() = default;
	virtual void execute(Entity*, double) noexcept = 0;
};

class StateMachineComponent : public Component
{
private:
    std::unordered_map<std::string, std::shared_ptr<State>> _states;
    std::shared_ptr<State> _current_state;
    std::string _current_state_name = "";

public:
    //update will call execute on the current state
    void update(double) override;
    void render() override { }
    explicit StateMachineComponent(Entity* p);
    StateMachineComponent() = delete;
    //addState will add a value to the map
    void addState(const std::string&, std::shared_ptr<State>) noexcept;
    //getState will retrieve a value from map
    std::shared_ptr<State> getState(const std::string&) const noexcept;
    //removeState will remove a value from map
    void removeState(const std::string&) noexcept;
    //changeState will change current state to the named state by retrieving it from map
    void changeState(const std::string&) noexcept;
    const std::string& currentState() const { return _current_state_name; }
};