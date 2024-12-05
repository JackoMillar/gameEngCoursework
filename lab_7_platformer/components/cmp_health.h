#pragma once

#include <ecm.h>

class HealthPointComponent : public Component{
protected:
    int hitPoints;
    int maxHP;
public:
    void hurt(int damage);
    void heal(int healing);
    void update(double dt) override;
    void render() override;
    explicit HealthPointComponent(Entity* p, int maxHp);
    HealthPointComponent() = delete;
    ~HealthPointComponent() override = default;
};