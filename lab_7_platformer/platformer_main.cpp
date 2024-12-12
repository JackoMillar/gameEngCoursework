#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"

using namespace std;

MenuScene menu;
Menu2Scene menu2;
Level1Scene level1;
Level2Scene level2;
Level3Scene level3;

extern EntityManager entityManager;
int exitcd = 120;
static shared_ptr<Entity> score;

EntityManager entityManager;

int main() {
  Engine::Start(1280, 720, "Circle: The Last Edgebender",&menu);
}