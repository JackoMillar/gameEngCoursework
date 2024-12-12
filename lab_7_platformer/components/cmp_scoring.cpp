#include "cmp_scoring.h"
#include "cmp_scoring_manager.h"
#include <system_renderer.h>
#include <system_resources.h>
#include "../game.h"

int lvl = 0;
double scale = 1.1;

ScoreComponent::ScoreComponent(Entity* parent, const std::string& fontFile)
    : Component(parent), _score(0), _string("Score: " + std::to_string(ScoreManager::GetScore())) {
    // Set up the text for score display
    _text.setString(_string);
    // Set font
    _font = Resources::get<sf::Font>(fontFile);
    _text.setFont(*_font);
    // Set size and color
    _text.setCharacterSize(24);
    _text.setFillColor(sf::Color::Red);
}

/* 
 Add score to player
 store score in scoreManager
*/
void ScoreComponent::addScore(int amount) {
    ScoreManager::AddScore(amount*scale); // Update the global score
    _string = "Score: " + std::to_string(ScoreManager::GetScore()); // Update the string
    _text.setString(_string); // Update the text
}

void ScoreComponent::update(double dt) {
    sf::Vector2f parentPosition = _parent->getPosition();
    _text.setPosition(parentPosition.x - 60.f, parentPosition.y - 70.f);
    if (rnd != lvl){
        rnd = lvl;
        scale = 1.1;
    }else if(scale > 0){
        scale-=0.02*dt;
    }
    
}

void ScoreComponent::render() {
    // Render the score to the screen
    Renderer::queue(&_text);
}

int ScoreComponent::getScore() const {
    // Grab score from scoreManager
    return ScoreManager::GetScore();
}
