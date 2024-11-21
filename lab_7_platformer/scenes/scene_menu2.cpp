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
    auto t = title->addComponent<TextComponent>("Circle: The Last Edgebender...");
    title->setPosition(Vector2f(Engine::getWindowSize().x * .315f, Engine::getWindowSize().y * .05f));
    //add icon to screen
    Texture iconfile;
    auto iconentity = makeEntity();
    if (!iconfile.loadFromFile("res/images/icon.png")) {
    cerr << "Failed to load spritesheet!" << std::endl;}
    auto icon = iconentity->addComponent<SpriteComponent>();
    auto ptr = make_shared<Texture>(iconfile);
    icon->setTexure(ptr);
    iconentity->setPosition(Vector2f(Engine::getWindowSize().x * .25f, Engine::getWindowSize().y * .1f));
    //add Play Game prompt to screen
    auto play = makeEntity();
    auto p = play->addComponent<TextComponent>("Play Game!\n   (Space)");
    play->setPosition(Vector2f(Engine::getWindowSize().x * .1f, Engine::getWindowSize().y * .85f));
    //add Endless prompt to screen
    auto endless = makeEntity();
    auto e = endless->addComponent<TextComponent>("Endless Mode!\n(Coming Soon)");
    endless->setPosition(Vector2f(Engine::getWindowSize().x * .3f, Engine::getWindowSize().y * .85f));
    //add Settings prompt to screen
    auto settings = makeEntity();
    auto s = settings->addComponent<TextComponent>("      Settings!\n(Coming Soon)");
    settings->setPosition(Vector2f(Engine::getWindowSize().x * .55f, Engine::getWindowSize().y * .85f));
    //add Quit Game prompt to screen
    auto quit = makeEntity();
    auto q = quit->addComponent<TextComponent>("Quit Game!\n   (Escape)");
    quit->setPosition(Vector2f(Engine::getWindowSize().x * .75f, Engine::getWindowSize().y * .85f));
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
