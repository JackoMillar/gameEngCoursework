#include "scene_level1.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_health.h"
#include "../components/cmp_scoring.h"
#include "../components/cmp_scoring_manager.h"
#include "../components/cmp_enemy_ai.h"
#include "../components/cmp_state_machine.h"
//#include "../components/cmp_enemy_states.h"
#include "../components/steering_decisions.h"
#include "../components/steering_states.h"
#include "../game.h"
#include "../components/cmp_text.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include <random>
#include <Box2D/Dynamics/b2Body.h>

using namespace std;
using namespace sf;

extern EntityManager entityManager;
static shared_ptr<Entity> player;
double exitcd = 2;
static shared_ptr<Entity> score;

void Level1Scene::Load() {
    cout << " Scene 1 Load" << endl;
    ls::loadLevelFile("res/level_1.txt", 40.0f);

    // Load Game Window
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
        player->addComponent<OnGroundAbilityComponent>();
        player->addComponent<HealthPointComponent>(50);
        // Add ScoreComponent directly to the player
        player->addComponent<ScoreComponent>();
        entityManager.addEntity(player);
    }

  //creating enemies
  //Setup C++ random number generation
  random_device dev;
  default_random_engine engine(dev());

  uniform_real_distribution<float> x_dist(0.0f, Engine::GetWindow().getSize().x);
  uniform_real_distribution<float> y_dist(0.0f, Engine::GetWindow().getSize().y);

  for (size_t n = 0; n < 5; ++n) 
  {
      auto TriEnemy = makeEntity();
      TriEnemy->setPosition(Vector2f(x_dist(engine), y_dist(engine)));
      auto s = TriEnemy->addComponent<ShapeComponent>();
      s->setShape<sf::CircleShape>(16.f, 3);
      s->getShape().setFillColor(Color::Yellow);
      TriEnemy->addComponent<SteeringComponent>(player.get());
      auto p = TriEnemy->addComponent<PhysicsComponent>(true, Vector2f(27.f, 27.f));
      p->setWeightless();

      //the enemy states
      auto sm = TriEnemy->addComponent<StateMachineComponent>();
      sm->addState("stationary", make_shared<StationaryState>());
      sm->addState("seek", make_shared<SeekState>(TriEnemy, player));
      sm->addState("flee", make_shared<FleeState>(TriEnemy, player));

      //decisions for enemy behavior
      auto decision = make_shared<DistanceDecision>
          (
              player,
              100.0f,
              make_shared<FleeDecision>(),
              make_shared<DistanceDecision>(
                  player,
                  50.0f,
                  make_shared<RandomDecision>(
                      make_shared<SeekDecision>(),
                      make_shared<StationaryDecision>()),
                  make_shared<SeekDecision>())
          );
      TriEnemy->addComponent<DecisionTreeComponent>(decision);
  }

  /*
  * //square enemies
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
    if(true /*ENEMY DEATH CHECK HERE*/){
        // Count down 2 seconds
        if(exitcd!=0){
            exitcd-=dt;
            if(exitcd < 0){
                exitcd = 0;
            }
        }
        else{
            // Check if the player has reached the end tile
            if (ls::getTileAt(player->getPosition()) == ls::END) {
                exitcd = 120;
                ls::setColor(ls::END, Color::Red);
                Engine::ChangeScene((Scene*)&level2);
                return;
            }

        }
    }
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

        // Update the score entity's position to follow the screen
        auto scoreEntities = entityManager.find("score");
        if (!scoreEntities.empty()) {
            auto score = scoreEntities[0];
            sf::Vector2f viewCenter = view.getCenter();
            sf::Vector2f viewSize = view.getSize();
            score->setPosition(sf::Vector2f(viewCenter.x - viewSize.x / 2.f + 20.f, viewCenter.y - viewSize.y / 2.f + 20.f));
            
        }

    // Call the base update
    Scene::Update(dt);
}


void Level1Scene::Render() {
    // Render the level and other entities
    ls::render(Engine::GetWindow());
    Scene::Render();

    // Render UI elements (like the score) in screen space
    sf::RenderWindow& window = Engine::GetWindow();
    sf::View originalView = window.getView(); // Save the current view
    window.setView(window.getDefaultView());  // Switch to default (screen space) view

    // Render score in screen space
    auto scoreEntities = entityManager.find("score");
    if (!scoreEntities.empty()) {
        scoreEntities[0]->render(); // Render the score entity
    }

    window.setView(originalView); // Restore the original view
}