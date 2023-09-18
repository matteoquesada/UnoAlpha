#include <iostream>
#include "../include/unoSource.h"
#include "../include/card.h"
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;


int main() {
    


    const int numCards = 10;
    Card* cards[numCards];

    for (int i = 0; i < numCards; ++i) {
        const std::string color = "red"; // Replace with your desired color
        int number = i; // Replace with your desired number
        std::cout << "color: " << color << std::endl;
        std::cout << "number: " << number << std::endl;
        cards[i] = new Card(color, number); // Allocate memory and store the pointer
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