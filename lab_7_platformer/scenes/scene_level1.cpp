#include "scene_level1.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>

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
  {
      //creating a triangle enemy
      auto triEnemy = makeEntity();
      triEnemy->setPosition(ls::getTilePosition(ls::findTiles(ls::ENEMY)[0]) +
          Vector2f(24.f, 30.f));
      auto s = triEnemy->addComponent<ShapeComponent>();
      //setting the triangle enemy shape
      s->setShape<sf::CircleShape>(18.f, 3);
      s->getShape().setFillColor(Color::Yellow);
      s->getShape().setOrigin(Vector2(18.f, 18.f));
  }

  {
      //creating a square enemy
      auto squareEnemy = makeEntity();
      squareEnemy->setPosition(ls::getTilePosition(ls::findTiles(ls::ENEMY2)[0]) +
          Vector2f(24.f, 24.f));
      auto s = squareEnemy->addComponent<ShapeComponent>();
      //setting the square enemy shape
      s->setShape<sf::RectangleShape>(Vector2f(30.f, 30.f));
      s->getShape().setFillColor(Color::Blue);
      s->getShape().setOrigin(Vector2(15.f, 15.f));
  }

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
