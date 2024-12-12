#pragma once
#include "cmp_physics.h"
#include <ecm.h>

class HurtComponent : public Component {
protected:
    std::weak_ptr<Entity> _player; // Weak reference to avoid circular dependency
    int _damage;

public:
    void setPlayer(const std::shared_ptr<Entity>& player) {
        _player = player;
    }

    void update(double dt) override;
    void render() override {}
    explicit HurtComponent(Entity* p, int damage);
    HurtComponent() = delete;
};
