#include "scene_level1.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_enemy_ai.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include <random>

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;

void Level1Scene::Load() {
  cout << " Scene 1 Load" << endl;
  ls::loadLevelFile("res/level_1.txt", 40.0f);

  auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
  ls::setOffset(Vector2f(0, ho));

  // Create player
  {
    player = makeEntity();
    player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
    auto s = player->addComponent<ShapeComponent>();
    s->setShape<sf::CircleShape>((20.f));
    s->getShape().setFillColor(Color::Red);
    s->getShape().setOrigin(Vector2f(20.f, 20.f));

    player->addComponent<PlayerPhysicsComponent>(Vector2f(40.f, 40.f));
  }

  //creating enemies
  //Setup C++ random number generation
  random_device dev;
  default_random_engine engine(dev());

  uniform_real_distribution<float> x_dist(0.0f, Engine::GetWindow().getSize().x);
  uniform_real_distribution<float> y_dist(0.0f, Engine::GetWindow().getSize().y);

  for (size_t n = 0; n < 5; ++n) {
      auto TriEnemy = makeEntity();
      TriEnemy->setPosition(Vector2f(x_dist(engine), y_dist(engine)));
      auto s = TriEnemy->addComponent<ShapeComponent>();
      s->setShape<sf::CircleShape>(16.f, 3);
      s->getShape().setFillColor(Color::Yellow);
      TriEnemy->addComponent<SteeringComponent>(player.get());
  }
  /*
  for (size_t n = 0; n < 6; ++n) {
      auto SqEnemy = makeEntity();
      SqEnemy->setPosition(Vector2f(x_dist(engine), y_dist(engine)));
      auto s = SqEnemy->addComponent<ShapeComponent>();
      s->setShape<sf::RectangleShape>(Vector2f(30.f, 30.f));
      s->getShape().setFillColor(Color::Blue);
      SqEnemy->addComponent<SteeringComponent>(player.get());
  }
  */

  // Add physics colliders to level tiles.
  {
    auto walls = ls::findTiles(ls::WALL);
    for (auto w : walls) {
      auto pos = ls::getTilePosition(w);
      pos += Vector2f(20.f, 20.f); //offset to center
      auto e = makeEntity();
      e->setPosition(pos);
      e->addComponent<PhysicsComponent>(false, Vector2f(40.f, 40.f));
    }
    
  }

  //Simulate long loading times
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  cout << " Scene 1 Load Done" << endl;

  setLoaded(true);
}

void Level1Scene::UnLoad() {
  cout << "Scene 1 Unload" << endl;
  player.reset();
  ls::unload();
  Scene::UnLoad();
}

void Level1Scene::Update(const double& dt) {

  if (ls::getTileAt(player->getPosition()) == ls::END) {
    Engine::ChangeScene((Scene*)&level2);
  }
  Scene::Update(dt);
}

void Level1Scene::Render() {
  ls::render(Engine::GetWindow());
  Scene::Render();
}
