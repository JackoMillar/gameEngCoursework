#include "scene_menu2.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include "../components/cmp_sprite.h"
#include <iostream>
#include "engine.h"

using namespace std;
using namespace sf;

void Menu2Scene::Load() {
  cout << "Menu Load \n";
  {
    //add title to screen
    auto title = makeEntity();
    auto t = title->addComponent<TextComponent>("THIS IS THE MAIN MENU\n(jack is a lil crazy ngl)");
    title->setPosition(Vector2f(Engine::getWindowSize().x * .315f, Engine::getWindowSize().y * .05f));
    //add icon to screen
    Texture iconfile;
    auto iconentity = makeEntity();
    if (!iconfile.loadFromFile("res/images/icon.png")) {
    cerr << "Failed to load spritesheet!" << std::endl;}
    auto icon = iconentity->addComponent<SpriteComponent>();
    auto ptr = make_shared<Texture>(iconfile);
    icon->setTexure(ptr);
    iconentity->setPosition(Vector2f(Engine::getWindowSize().x * .25f, Engine::getWindowSize().y * .15f));
    //add prompt to screen
    auto prompt = makeEntity();
    auto p = prompt->addComponent<TextComponent>("Press the space bar\n          to start!");
    prompt->setPosition(Vector2f(Engine::getWindowSize().x * .385f, Engine::getWindowSize().y * .58f));
  }
  setLoaded(true);
}

void Menu2Scene::Update(const double& dt) {
  // cout << "Menu Update "<<dt<<"\n";

  if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
    Engine::ChangeScene(&level1);
  }

  Scene::Update(dt);
}
