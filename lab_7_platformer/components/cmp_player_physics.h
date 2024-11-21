#pragma once

#include "cmp_physics.h"
#include "maths.h"
#include "engine.h"


class Scene;
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
        printf("Player touched the ground! Activating ability...\n");
        auto compatibleComponents = _parent->GetCompatibleComponent<PlayerPhysicsComponent>();
        if (!compatibleComponents.empty()) {
            
            // When the ball hits the ground, do AOE attack

            float aoe = 100.f;
            auto playerPosition = _parent->getPosition();
            //_parent->setForDelete();

            printf("AOE Attack triggered at position: (%.2f, %.2f)\n", playerPosition.x, playerPosition.y);

            auto nearbyEntities = findEntitiesInRange(playerPosition, aoe);
            for (auto& entity : nearbyEntities) {
                applyDamage(entity.get());  
            }
        }
    }


    std::vector<std::shared_ptr<Entity>> findEntitiesInRange(const sf::Vector2f& position, float radius) {
        std::vector<std::shared_ptr<Entity>> result;

        auto sceneParent = dynamic_cast<Scene*>(_parent);
        if (sceneParent) {
            for (auto& entity : sceneParent->getAllEntities()) {
                // Skip if the entity is the player (we don't want to delete the player)
                printf("test1\n");
                if (entity.get() == _parent) {
                    continue;
                }
                printf("test2\n");
                const auto entityPos = entity->getPosition();
                const float distance = std::hypot(entityPos.x - position.x, entityPos.y - position.y);  // Calculate the distance
                if (distance <= radius) {
                    result.push_back(entity);  // Add to result if it's within range and is not the player
                }
                printf("test3\n");
            }
        }
        else {
            // Handle the case where _parent is not a Scene or invalid
            printf("Error: _parent is not a Scene or is invalid!\n");
        }

        return result;
    }

    void applyDamage(Entity* entity) {
        // Example: Assume entities have a health component
        entity->is_fordeletion(); 
    }

    /*void createAOEVisualEffect(const sf::Vector2f& position, float radius) {
        auto aoeEffect = makeEntity();
        auto shape = aoeEffect->addComponent<ShapeComponent>();
        shape->setShape<sf::CircleShape>(radius);
        shape->getShape().setFillColor(sf::Color(255, 0, 0, 100)); // Semi-transparent red
        shape->getShape().setPosition(position);
        printf("AOE Visual Effect created at (%.2f, %.2f)\n", position.x, position.y);

        // Destroy the effect after a short delay (pseudo-code)
        aoeEffect->scheduleDestruction(1.0f); // Destroy in 1 second
    }*/
};