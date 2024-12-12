#pragma once

#include <SFML/Graphics/text.hpp>
#include <ecm.h>

class ScoreComponent : public Component {
public:
    ScoreComponent(Entity* parent, const std::string& fontFile = "centurygothic.ttf");
    void update(double dt) override;
    void render() override;

    void addScore(int amount); 
    int getScore() const; 

    ~ScoreComponent() override = default;

protected:
    std::string _string;
    sf::Text _text;
    std::shared_ptr<sf::Font> _font;
    int _score;
};
