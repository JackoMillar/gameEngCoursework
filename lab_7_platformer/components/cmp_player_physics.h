#pragma once

#include "cmp_physics.h"
#include "maths.h"
#include "engine.h"
#include "system_physics.h"
#include "cmp_player_abilities.h"
#include "../components/cmp_scoring.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>


class Scene;
extern EntityManager entityManager;
using namespace std;
using namespace sf;

class PlayerPhysicsComponent : public PhysicsComponent {
protected:
  b2Vec2 _size;
  sf::Vector2f _maxVelocity;
  bool _grounded;
  bool _walled;
  bool _roofed;
  float _groundspeed;

public:

  bool isGrounded() const;
  bool isWalled() const;
  bool isRoofed() const;

  void update(double dt) override;

  explicit PlayerPhysicsComponent(Entity* p, const sf::Vector2f& size);

  PlayerPhysicsComponent() = delete;
};

class OnGroundAbilityComponent : public Component {
public:
    OnGroundAbilityComponent(Entity* p) : Component(p) {}

    void update(double dt) override {
        
        auto components = _parent->get_components<PlayerPhysicsComponent>();
        if (!components.empty()) {
            
            auto playerPhysics = components[0];
            
            if (playerPhysics->isGrounded()) {
                executeAbility();
               
            }
        }
    }

    void render() override {
        // No specific rendering needed for this component
    }

private:
    void executeAbility() {
        
        auto compatibleComponents = _parent->get_components<PlayerPhysicsComponent>();
        if (!compatibleComponents.empty()) {
            
            // When the ball hits the ground, do AOE attack
            
            float aoe = 100.f;
            auto playerPosition = _parent->getPosition();

            printf("AOE Attack triggered at position: (%.2f, %.2f)\n", playerPosition.x, playerPosition.y);
            std::vector<std::shared_ptr<Entity>> allEntities = entityManager.list; // Replace with your actual logic
            
            float searchRadius = 200.0f;

            auto nearbyEntities = findEntitiesInRange(playerPosition, searchRadius, allEntities);
           
            for (const auto& entity : nearbyEntities) {
                printf("Entity found within range at: (%.2f, %.2f)\n", entity->getPosition().x, entity->getPosition().y);
                entity->markForDeletion();
                auto scoreComponent = _parent->GetCompatibleComponent<ScoreComponent>();
                if (!scoreComponent.empty() && entity->isVisible()) {
                    scoreComponent[0]->addScore(10); // Add 10 to the score when the player hits the ground
                    printf("SCORE ADDED");
                }
            }
        }
    }


    std::vector<std::shared_ptr<Entity>> findEntitiesInRange(
        const sf::Vector2f& position,
        float radius,
        const std::vector<std::shared_ptr<Entity>>& entities) {

        std::vector<std::shared_ptr<Entity>> result;
    
        for (const auto& entity : entities) {
            if (!entity) {
                printf("Warning: Null entity encountered.\n");
                continue;
            }
          
            // Skip if the entity is the same as _parent/player
            if (entity.get() == _parent) {
                printf("this is the player\n");
                continue;
            }
            const auto entityPos = entity->getPosition();
            const float distance = std::hypot(entityPos.x - position.x, entityPos.y - position.y);  // Calculate the distance
            if (distance <= radius) {
                result.push_back(entity);  // Add to result if within range
                printf("Entity at (%.2f, %.2f) added to result.\n", entityPos.x, entityPos.y);
            }
        }

        return result;
    }
};