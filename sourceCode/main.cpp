#include "main.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

//constant to store font for project
const Font font = Font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");

//function for player being on main menu
void menu(){
    Text title = new text("Main Menu", font, 30);
    Text normal = new text("Normal Mode", font, 20);
    Text endless = new text("Endless Mode (Coming Soon)", font, 20);
    Text settings = new text("Settings", font, 20);
    Text exit = new text("Close Game", font, 20);
}


Player player;

const int gameWidth = 800;
const int gameHeight = 600;

void Load() {
    // Set player to middle of the screen
    player.setPosition(Vector2f(gameWidth / 2.f, gameHeight / 2.f));    menu();
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
