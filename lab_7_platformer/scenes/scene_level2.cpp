#include "scene_level2.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;

void Level2Scene::Load() {
    cout << " Scene 2 Load" << endl;
    ls::loadLevelFile("res/level_2.txt", 40.0f);

    auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
    ls::setOffset(Vector2f(0, ho));

    // Set the initial view
    sf::View view(sf::FloatRect(0, 0, Engine::getWindowSize().x, Engine::getWindowSize().y));
    Engine::GetWindow().setView(view);

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
    cout << " Scene 2 Load Done" << endl;

    setLoaded(true);
}

void Level2Scene::UnLoad() {
    cout << "Scene 2 Unload" << endl;
    player.reset();
    ls::unload();
    Scene::UnLoad();
}

void Level2Scene::Update(const double& dt) {
    // Check if the player has reached the end tile
    if (ls::getTileAt(player->getPosition()) == ls::END) {
        Engine::ChangeScene((Scene*)&level3);
    }
    else{
    // Get current view and player position
    sf::View view = Engine::GetWindow().getView();
    sf::Vector2f playerPos = player->getPosition();

    // Calculate the bounds of the level in pixels
    sf::Vector2f levelSize(ls::getWidth() * 40.f, ls::getHeight() * 40.f);

    // Get the vertical offset set in the level system
    sf::Vector2f levelOffset = ls::getOffset();

    // Get half the window size
    sf::Vector2f halfWindowSize(Engine::getWindowSize().x / 2.f, Engine::getWindowSize().y / 2.f);

    // Clamp the view's center to the level bounds
    float clampedX = std::clamp(playerPos.x, halfWindowSize.x, levelSize.x - halfWindowSize.x);
    float clampedY = std::clamp(playerPos.y, halfWindowSize.y + levelOffset.y, levelSize.y - halfWindowSize.y + levelOffset.y);

    // Update the view center
    view.setCenter(clampedX, clampedY);
    Engine::GetWindow().setView(view);

    // Call the base update
    Scene::Update(dt);
    }
}


void Level2Scene::Render() {
    ls::render(Engine::GetWindow());
    Scene::Render();
}