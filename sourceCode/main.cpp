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


void Load() {
    menu();
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
}

void Render(RenderWindow& window) {
    // Draw Everything
}

int main() {
    RenderWindow window(VideoMode(800, 600), "Ball!");
    Load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}