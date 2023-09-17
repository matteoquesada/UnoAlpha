#include <iostream>
#include "../include/unoSource.h"

#include <SFML/Graphics.hpp>
using namespace sf;


int main() {
    // WINDOW/CANVAS CREATION
    RenderWindow window(VideoMode(1280, 720), "UNO Alpha 1.2.0");

    // SPRITE & TEXTURE OBJECTS
    // INITIALIZE MAIN MENU RESOURCES
    initializeMainMenuResources();

    bool inGame = true;
    int currentDisplay = 0;

    while (window.isOpen() && inGame) {
        switch (currentDisplay) {
        case 0: {
            handleMainMenu(window, currentDisplay);
            std::cout << "case 0" << std::endl;
            break;
        }
        case 1: {
            handleGameModeMenu(window, currentDisplay);
            std::cout<< "case 1" << std::endl;
            break;
        }
        case 2: {
            handleInGame(window, currentDisplay);
            std::cout << "case 2" << std::endl;
        }
        default:
            break;
        }

    return 0;
}

