#include "cmp_health.h"
#include <engine.h>
#include <system_renderer.h>
#include <system_resources.h>

int maxHP;
int hitPoints;

void HealthPointComponent::hurt(int damage){
    hitPoints -= damage;
    if(hitPoints < 0){
        _parent->setForDelete();
    }
}

void HealthPointComponent::heal(int healing){
    hitPoints += healing;
    if(hitPoints > maxHP){
        hitPoints = maxHP;
    }
}

void HealthPointComponent::update(double dt){}

void HealthPointComponent::render(){}

HealthPointComponent::HealthPointComponent(Entity *const p, int maxHp) : Component(p), maxHP(maxHp)
{
    hitPoints = maxHP;
}