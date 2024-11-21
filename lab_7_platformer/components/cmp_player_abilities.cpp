//cmp_player_abilties.cpp
#include "cmp_player_physics.h"
#include "cmp_player_abilities.h"


using namespace std;
using namespace sf;

/*class OnGroundAbilityComponent : public Component {
public:
    OnGroundAbilityComponent(Entity* p) : Component(p) {}
    
    void update(double dt) override {
        printf("test1\n");
        auto components = _parent->get_components<PlayerPhysicsComponent>();
        if (!components.empty()) { // Ensure at least one exists
            printf("test2\n");
            auto playerPhysics = components[0]; // Retrieve the first one
            printf("test3\n");
            if (playerPhysics->isGrounded()) {
                executeAbility();
                printf("test4\n");
            }
        }
    }


private:
    void executeAbility() {
        // Example ability: Increase player's speed temporarily
        printf("Player touched the ground! Activating ability...\n");
        auto compatibleComponents = _parent->GetCompatibleComponent<PlayerPhysicsComponent>();
        if (!compatibleComponents.empty()) {
            auto playerPhysics = compatibleComponents[0];
            // Example: Apply some velocity modification or action here
            playerPhysics->setVelocity(Vector2f(playerPhysics->getVelocity().x, -200.f)); // Example boost
        }
    }
};*/