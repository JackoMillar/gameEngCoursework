#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include "../components/cmp_sprite.h"
#include <iostream>
#include "engine.h"

using namespace std;
using namespace sf;

void MenuScene::Load() {
  cout << "Menu Load \n";
  {
    //add text to screen
    auto txt = makeEntity();
    auto t = txt->addComponent<TextComponent>(
        "Circle: The Last Edgebender\nPress Space to Start");
    //NOT CURRENTLY WORKING
    txt->setPosition(Vector2f(Engine::getWindowSize().x * .45f, .0f)); 
    //add icon to screen
    Texture iconfile;
    auto iconentity = makeEntity();
        if (!iconfile.loadFromFile("res/images/icon.png")) {
    cerr << "Failed to load spritesheet!" << std::endl;
  }
    auto icon = iconentity->addComponent<SpriteComponent>();
    auto ptr = make_shared<Texture>(iconfile);
    icon->setTexure(ptr);
    iconentity->setPosition(Vector2f(Engine::getWindowSize().x * .25f, Engine::getWindowSize().y * .15f));
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
