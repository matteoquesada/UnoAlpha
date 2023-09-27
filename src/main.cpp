#include "..//game.h"

int main() {

    // CREATE THE WINDOW AND SET THE FRAME RATE LIMIT TO 60 FPS IN ORDER TO SAVE RESOURCES
    sf::RenderWindow window(sf::VideoMode(1280, 720), "UNO Alpha 1.5.5");
    window.setFramerateLimit(15);

    // CREATE THE GAME OBJECT
    Game game;

    // RUN THE GAME LOOP BY CALLING THE RUN FUNCTION
    game.run(window);

    return 0;
}
