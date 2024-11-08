#include "main.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

Player player;

const int gameWidth = 800;
const int gameHeight = 600;

void Load() {
    // Set player to middle of the screen
    player.setPosition(Vector2f(gameWidth / 2.f, gameHeight / 2.f));
}

void Update(RenderWindow& window) {

    // Reset clock, recalculate deltatime
    static Clock clock;
    float dt = clock.restart().asSeconds();
    // check and consume events
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
            return;
        }
    }
    // Quit Via ESC Key
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.close();
    }
    player.Update(dt);

}

void Render(RenderWindow& window) {
    player.Render(window);
}

int main() {
    RenderWindow window(VideoMode(gameWidth, gameHeight), "Circle: The Last Edgebender");
    Load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}
