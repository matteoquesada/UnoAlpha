#include "../include/unoSource.h"
#include <iostream>
#include "../include/card.h"
#include <SFML/Graphics.hpp>

// SPRITE & TEXTURE OBJECTS
Texture wallpaperTexture;
Sprite wallpaperSprite;

Texture wallpapergGameModeTexture;
Sprite wallpaperGameModeSprite;

Texture logoTexture;
Sprite logoSprite;
Sprite shadowSprite;

Texture buttonPVPTexture;
Sprite buttonPVPSprite;

Texture buttonPVETexture;
Sprite buttonPVESprite;

void initializeMainMenuResources() {
    // INITIALIZE MAIN WALLPAPER
    wallpaperTexture.loadFromFile("assets/wallpaper.png");
    wallpaperSprite.setTexture(wallpaperTexture);
    wallpaperSprite.setPosition(0, 0);

    // INITIALIZE GAME MODE WALLPAPER
    wallpapergGameModeTexture.loadFromFile("assets/wallpaperGameMode.png");
    wallpaperGameModeSprite.setTexture(wallpapergGameModeTexture);
    wallpaperGameModeSprite.setPosition(0, 0);

    // INITIALIZE LOGO
    logoTexture.loadFromFile("assets/logo.png");
    logoSprite.setTexture(logoTexture);
    logoSprite.setPosition(330, 165);
    logoSprite.setScale(0.5f, 0.5f);

    // INITIALIZE SHADOW LOGO
    shadowSprite.setTexture(logoTexture);
    shadowSprite.setColor(Color(0, 0, 0, 200));
    shadowSprite.setPosition(logoSprite.getPosition().x + 10, logoSprite.getPosition().y + 10);
    shadowSprite.setScale(0.5f, 0.5f);

    // INITIALIZE BUTTONS
    buttonPVPTexture.loadFromFile("assets/buttonPVP.png");
    buttonPVPSprite.setTexture(buttonPVPTexture);
    buttonPVPSprite.setPosition(380, 165);

    buttonPVETexture.loadFromFile("assets/buttonPVE.png");
    buttonPVESprite.setTexture(buttonPVETexture);
    buttonPVESprite.setPosition(380, 500);
}

void initializeCardResources() {
    const char* colors[] = { "red", "yellow", "green", "blue" };
    const int maxNumber = 9;

    int cardIndex = 0;

    





}

void handleMainMenu(RenderWindow& window, int& currentDisplay) {
    // BOOLEAN TO DETERMINE IF MOUSE ON TOP OF LOGO
    bool mouseOnButton = false;
    bool buttonPressed = false;

    // HANDLE MOUSE EVENTS
    Event event;

    // CHECK IF THE MOUSE IS HOVERING ON THE LOGO
    Vector2i mousePos = Mouse::getPosition(window);
    mouseOnButton = logoSprite.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    // Use a flag to track if the button was pressed
    static bool buttonClicked = false;

    while (window.pollEvent(event)) {
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            buttonPressed = true;
        }
        else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
            buttonPressed = false;
            if (mouseOnButton && buttonClicked) {
                std::cout << "Button pressed" << std::endl;
                logoSprite.setColor(Color(150, 150, 150, 255)); // BUTTON PRESSED ON LOGO
                currentDisplay = 1;
            }
            buttonClicked = false; // RESET THE BUTTON CLICK FLAG
        }
    }

    if (mouseOnButton && !buttonPressed) {
        logoSprite.setColor(Color(200, 200, 200, 255)); // MOUSE HOVER COLOR DIMMED
        buttonClicked = true; // SET THE BUTTON CLICK FLAG WHEN THE MOUSE IS RELEASED
    }
    else if (!mouseOnButton && !buttonPressed) {
        logoSprite.setColor(Color(255, 255, 255, 255)); // DEFAULT STATE
    }

    window.clear(); // CLEAR THE WINDOW TO AVOID OVERLAPPING
    window.draw(wallpaperSprite); // DRAW THE WALLPAPER FIRST
    window.draw(shadowSprite); // DRAW THE SHADOW
    window.draw(logoSprite); // DRAW THE LOGO ON TOP OF SHADOW
    window.display(); // DISPLAY THE WINDOW
}


void handleGameModeMenu(RenderWindow& window, int& currentDisplay) {

    // CHECK IF THE CURRENT DISPLAY IS THE GAME MODE MENU
    if (currentDisplay != 1) {
        return;
    }

    // BOOLEAN TO DETERMINE IF MOUSE ON TOP OF BUTTONS
    bool mouseOnButtonPVP = false;
    bool mouseOnButtonPVE = false;

    // CHECK IF THE MOUSE IS ON THE BUTTONS
    Vector2i mousePos = Mouse::getPosition(window);
    mouseOnButtonPVP = buttonPVPSprite.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    mouseOnButtonPVE = buttonPVESprite.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    // USE A FLAG TO TRACK IF THE BUTTON WAS CLICKED
    static bool buttonClicked = false;

    // HANDLE MOUSE EVENTS
    Event event;

    // HANDLE MOUSE EVENTS
    while (window.pollEvent(event)) {
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            if (mouseOnButtonPVP) {
                // BUTTON PVP WAS CLICKED
                buttonPVPSprite.setColor(Color(100, 100, 100, 255));
                std::cout << "Button PVP pressed" << std::endl;
                buttonClicked = true; // SET THE BUTTON CLICK FLAG
                //currentDisplay = 2;
            }
            else if(mouseOnButtonPVE) {
                // BUTTON PVE WAS CLICKED
				buttonPVESprite.setColor(Color(100, 100, 100, 255)); 
				std::cout << "Button PVE pressed" << std::endl;
				buttonClicked = true; // SET THE BUTTON CLICK FLAG
				currentDisplay = 3;
			}
           
        }
        else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
            // BUTTON PVP/PVE WAS RELEASED
            if (buttonClicked) {
                // RESET buttonClicked FLAG
                buttonClicked = false;
            }
        }

    }

    // CHANGE THE COLOR OF THE BUTTONS WHEN MOUSE HOVER
    if (mouseOnButtonPVP && !buttonClicked) {
        buttonPVPSprite.setColor(Color(200, 200, 200, 255)); // MOUSE HOVER
    }
    else if (!mouseOnButtonPVP && !buttonClicked) {
        buttonPVPSprite.setColor(Color(255, 255, 255, 255)); // DEFAULT STATE
    }

    if (mouseOnButtonPVE && !buttonClicked) {
		buttonPVESprite.setColor(Color(200, 200, 200, 255)); // MOUSE HOVER
	}
    else if (!mouseOnButtonPVE && !buttonClicked) {
		buttonPVESprite.setColor(Color(255, 255, 255, 255)); // DEFAULT STATE
	}

    // DRAW THE WINDOW
    window.clear(); // CLEAR THE WINDOW TO AVOID OVERLAPPING
    window.draw(wallpaperGameModeSprite); // DRAW THE WALLPAPER FIRST
    window.draw(buttonPVPSprite); // DRAW THE BUTTON PVP
    window.draw(buttonPVESprite); // DRAW THE BUTTON PVE
    window.display(); // DISPLAY THE OVERALL WINDOW
}

void handleInGamePVE(RenderWindow& window, int& currentDisplay){
    // CHECK IF THE CURRENT DISPLAY IS THE CORRESPONDING GAME MODE 
    if (currentDisplay != 3) {
        return;
    }




}
