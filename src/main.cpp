#include <iostream>
#include "../include/unoSource.h"

#include <SFML/Graphics.hpp>
using namespace sf;


int main() {
    // WINDOW/CANVAS CREATION
    RenderWindow window(sf::VideoMode(1280, 720), "UNO Alpha 1.0.1");

    // SPRITE & TEXTURE OBJECTS
    Texture wallpaperTexture;
    Sprite wallpaperSprite;
    Texture logoTexture;
    Sprite logoSprite;
    Sprite shadowSprite;

    // GAME MODE MENU SELECTED FLAG
    bool gameModeMenuActive = false;

    // INITIALIZE MAIN MENU RESOURCES
    initializeMainMenuResources(wallpaperTexture, wallpaperSprite, logoTexture, logoSprite, shadowSprite);

    // DISPLAY MAIN MENU
    handleMainMenu(window, wallpaperSprite, logoSprite, shadowSprite);

    return 0;
}

