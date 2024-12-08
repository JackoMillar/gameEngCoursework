#pragma once

#include <SFML/Graphics/text.hpp>
#include <ecm.h>

class ScoreComponent : public Component {
public:
    ScoreComponent(Entity* parent, const std::string& fontFile = "centurygothic.ttf");
    void update(double dt) override;
    void render() override;

    void addScore(int amount); // Method to add to the score
    int getScore() const; // Method to get the current score

    ~ScoreComponent() override = default;

protected:
    std::string _string;
    sf::Text _text;
    std::shared_ptr<sf::Font> _font;
    int _score; // Store the score
};