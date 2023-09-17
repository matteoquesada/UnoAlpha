#include <iostream>
#include "../include/unoSource.h"

#include <SFML/Graphics.hpp>
using namespace sf;


int main() {

    // WINDOW/CANVAS CREATION
    RenderWindow window(VideoMode(1280, 720), "UNO Alpha 1.3.0");

    // SPRITE & TEXTURE OBJECTS
    // INITIALIZE MAIN MENU RESOURCES
    initializeMainMenuResources();

    // INITIALIZE BASE MAIN MENU AS DEFAULT DISPLAY
    int currentDisplay = 0;

    // MAIN LOOP
    while (window.isOpen()) {
        // currentDisplay HANDLER SWITCH
        switch (currentDisplay) {
        case 0: {
            // HANDLE MAIN MENU
            handleMainMenu(window, currentDisplay);
            std::cout << "case 0" << std::endl;
            break;
        }
        case 1: {
            // HANDLE GAME MODE MENU
            handleGameModeMenu(window, currentDisplay);
            std::cout << "case 1" << std::endl;
            break;
        }
        case 2: {
            // HANDLE IN-GAME PVP
            //handleInGamePVP(window, currentDisplay);
            std::cout << "case 2" << std::endl;
            break;
        }
        case 3: {
            // HANDLE IN-GAME PVE
            handleInGamePVE(window, currentDisplay);
            std::cout << "case 3" << std::endl;
            break;
        }
        default:
            break;
        }
    }

    return 0;

}