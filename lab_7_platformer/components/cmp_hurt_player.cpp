#include "cmp_hurt_player.h"
#include "cmp_health.h"
#include <engine.h>

using namespace std;
using namespace sf;

int damage;
int const pldamage=5; //set damage dealt by player collision to 5, change here if needed

void HurtComponent::update(double dt) {
  if (auto pl = _player.lock()) {
    if (length(pl->getPosition() - _parent->getPosition()) < 25.0) {
      auto plhealth = pl->GetCompatibleComponent<HealthPointComponent>();
      plhealth[0]->hurt(damage);
      auto health = _parent->GetCompatibleComponent<HealthPointComponent>();
      health[0]->hurt(pldamage);
    }
  }
}

HurtComponent::HurtComponent(Entity* p, int d)
    : Component(p), _player(_parent->scene->ents.find("player")[0]) {damage = d;}
