#include "../include/unoSource.h"
#include <iostream>

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
    wallpaperGameModeSprite.setTexture(wallpapergGameModeTexture;
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
    buttonPVPSprite.setPosition(330, 165);

    buttonPVETexture.loadFromFile("assets/buttonPVE.png");
    buttonPVESprite.setTexture(buttonPVETexture);
    buttonPVESprite.setPosition(330, 500);
}

void handleMainMenu(RenderWindow& window, int& currentDisplay) {
    // BOOLEAN TO DETERMINE IF MOUSE ON TOP OF LOGO
    bool mouseOnButton = false;
    bool buttonPressed = false;

    // HANDLE MOUSE EVENTS
    Event event;

    // Check if the mouse is on the logo FACTORIZABLE TODAS LAS ACCIONES DEL BOTON
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
            buttonClicked = false; // Reset the button click flag
        }
    }

    if (mouseOnButton && !buttonPressed) {
        logoSprite.setColor(Color(200, 200, 200, 255)); // Mouse hover
        buttonClicked = true; // Set the button click flag when the mouse is released
    }
    else if (!mouseOnButton && !buttonPressed) {
        logoSprite.setColor(Color(255, 255, 255, 255)); // Default state
    }

    window.clear(); // CLEAR THE WINDOW TO AVOID OVERLAPPING
    window.draw(wallpaperSprite); // DRAW THE WALLPAPER FIRST
    window.draw(shadowSprite); // DRAW THE SHADOW
    window.draw(logoSprite); // DRAW THE LOGO ON TOP OF SHADOW
    window.display(); // DISPLAY THE WINDOW
}


void handleGameModeMenu(RenderWindow& window, int& currentDisplay) {
    if (currentDisplay != 1) {
        // If not in the game mode menu state, return early and don't handle mouse events
        return;
    }

    bool mouseOnButton = false;
    bool buttonPressed = false;

    // HANDLE MOUSE EVENTS
    Event event;

    // Check if the mouse is on the PVP button
    Vector2i mousePos = Mouse::getPosition(window);
    mouseOnButton = buttonPVPSprite.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    // Use a flag to track if the button was pressed
    static bool buttonClicked = false;

    while (window.pollEvent(event)) {
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            buttonPressed = true;
        }
        else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
            buttonPressed = false;
            if (mouseOnButton && buttonClicked) {
                // The button was clicked
                buttonPVPSprite.setColor(Color(100, 100, 100, 255)); // BUTTON PRESSED ON LOGO
                std::cout << "Button PVP pressed" << std::endl;
            }
            buttonClicked = false; // Reset the button click flag
        }
    }

    if (mouseOnButton && !buttonPressed) {
        buttonPVPSprite.setColor(Color(200, 200, 200, 255)); // Mouse hover
        buttonClicked = true; // Set the button click flag when the mouse is released
    }
    else if (!mouseOnButton && !buttonPressed) {
        buttonPVPSprite.setColor(Color(255, 255, 255, 255)); // Default state
    }

    window.clear(); // CLEAR THE WINDOW TO AVOID OVERLAPPING
    window.draw(wallpaperGameModeSprite); // DRAW THE WALLPAPER FIRST
    window.draw(buttonPVPSprite); // DRAW THE BUTTONS
    window.draw(buttonPVESprite);
    window.display(); // DISPLAY THE WINDOW
}

void handleInGame(RenderWindow& window, int& currentDisplay) {
    if (currentDisplay != 2) {
		// If not in the in-game state, return early and don't handle mouse events
		return;
	}

	// Handle in-game logic here
}

