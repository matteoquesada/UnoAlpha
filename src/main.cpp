#include <iostream>
#include "../include/unoSource.h"
#include "../include/card.h"
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;


int main() {
    


    const int numColors = 4; // Red, Blue, Yellow, Green
    const int numNumbers = 10; // 0-9

    Card* cards[numColors * numNumbers];

    for (int colorIndex = 0; colorIndex < numColors; ++colorIndex) {
        std::string color;

        switch (colorIndex) {
        case 0:
            color = "red";
            break;
        case 1:
            color = "blue";
            break;
        case 2:
            color = "yellow";
            break;
        case 3:
            color = "green";
            break;
        default:
            color = "red"; // Default to red for unsupported colors
        }

        for (int number = 0; number < numNumbers; ++number) {
            cards[colorIndex * numNumbers + number] = new Card(color, number);
        }
    }


    // WINDOW/CANVAS CREATION
    RenderWindow window(VideoMode(1280, 720), "UNO Alpha 1.4.0");

    // SPRITE & TEXTURE OBJECTS
    // INITIALIZE MAIN MENU RESOURCES
    initializeMainMenuResources();

    // INITIALIZE CARD RESOURCES


    // INITIALIZE BASE MAIN MENU AS DEFAULT DISPLAY
    int currentDisplay = 0;

    // MAIN LOOP
    while (window.isOpen()) {
        // currentDisplay HANDLER SWITCH
        switch (currentDisplay) {
        case 0: {
            // HANDLE MAIN MENU
            handleMainMenu(window, currentDisplay);
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