#include "cmp_hurt_player.h"
#include "cmp_health.h"
#include <engine.h>
#include <iostream>

using namespace std;

void HurtComponent::update(double dt) {
    if (auto pl = _player.lock()) { // Ensure the player entity is still valid
        auto enemyPhysics = _parent->GetCompatibleComponent<PhysicsComponent>();
        auto playerPhysics = pl->GetCompatibleComponent<PhysicsComponent>();
        // Check if the PhysicsComponents exist and are colliding
        if (!enemyPhysics.empty() && !playerPhysics.empty() &&
            enemyPhysics[0]->isTouching(*playerPhysics[0])) {
            // Apply damage to the player
            auto playerHealth = pl->GetCompatibleComponent<HealthPointComponent>();
            if (!playerHealth.empty()) {
                playerHealth[0]->hurt(_damage); // Hurt the player
                cout << "Player hurt for " << _damage << " damage!" << endl;
            }
            // Optional: Hurt the enemy as well (if necessary)
            auto enemyHealth = _parent->GetCompatibleComponent<HealthPointComponent>();
            if (!enemyHealth.empty()) {
                enemyHealth[0]->hurt(5); // Deal 5 damage to the enemy
                cout << "Enemy damaged by collision!" << endl;
            }
        }
    }
}

HurtComponent::HurtComponent(Entity* p, int damage) : Component(p), _damage(damage) {}
