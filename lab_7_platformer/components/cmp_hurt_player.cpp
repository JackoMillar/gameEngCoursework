#include "cmp_hurt_player.h"
#include "cmp_health.h"
#include <engine.h>

using namespace std;
using namespace sf;

int damage;
int const pldamage=5; //set damage dealt by player collision to 5, change here if needed

void HurtComponent::update(double dt) {
    
  if (auto pl = _player.lock()) {
      printf("Teest");
    auto p = _parent->GetCompatibleComponent<PhysicsComponent>();
    auto plp = pl->GetCompatibleComponent<PhysicsComponent>();
    if(p[0]->isTouching(*plp[0])) {
      auto plhealth = pl->GetCompatibleComponent<HealthPointComponent>();
      plhealth[0]->hurt(damage);
      auto health = _parent->GetCompatibleComponent<HealthPointComponent>(); //NOT WORKING
      health[0]->hurt(pldamage);
      cout << "ow\n";
    }
  }

}

HurtComponent::HurtComponent(Entity* p, int d)
    : Component(p){damage = d;}
