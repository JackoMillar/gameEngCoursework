#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include "../components/cmp_sprite.h"
#include <iostream>

using namespace std;
using namespace sf;

void MenuScene::Load() {
  cout << "Menu Load \n";
  {
    Texture coconut;
    auto txt = makeEntity();
    auto t = txt->addComponent<TextComponent>(
        "Circle: The Last Edgebender\nPress Space to Start");
    auto shape = makeEntity();
        if (!coconut.loadFromFile("res/images/coconutj.jpg")) {
    cerr << "Failed to load spritesheet!" << std::endl;
  }
    auto s = shape->addComponent<SpriteComponent>();
    auto ptr = make_shared<Texture>(coconut);
    s->setTexure(ptr);
  }
  setLoaded(true);
}

void MenuScene::Update(const double& dt) {
  // cout << "Menu Update "<<dt<<"\n";

  if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
    Engine::ChangeScene(&level1);
  }

  Scene::Update(dt);
}
