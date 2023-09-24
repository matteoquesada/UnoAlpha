#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

// CLASSES & FUNCTIONS
#include "../include/unoSource.h"
#include "../include/card.h"
#include "../include/deck.h"


int main() {
    

    // WINDOW/CANVAS CREATION
    RenderWindow window(VideoMode(1280, 720), "UNO Alpha 1.4.5");

    // SPRITE & TEXTURE OBJECTS 
    // INITIALIZE MAIN MENU RESOURCES
    initializeMainMenuResources();


    // INITIALIZE BASE MAIN MENU AS DEFAULT DISPLAY
    int currentDisplay = 0;

    // MAIN LOOP RUNTIME HANDLER

    while (window.isOpen()) {
        // currentDisplay HANDLER SWITCH
        switch (currentDisplay) {
        case 0: {
            // HANDLE MAIN MENU
            handleMainMenu(window, currentDisplay);
            //deck.displayDeck(window);
            break;
        }
        case 1: {
            // HANDLE GAME MODE MENU
            handleGameModeMenu(window, currentDisplay);
            break;
        }
        case 2: {
            // HANDLE IN-GAME PVP
            //handleInGamePVP(window, currentDisplay);
            break;
        }
        case 3: {
            // HANDLE IN-GAME PVE
            handleInGamePVE(window, currentDisplay);
            break;
        }
        default:
            break;
        }
    }

    return 0;

}