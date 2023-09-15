#include "../include/unoSource.h"
#include <iostream>

void initializeMainMenuResources(sf::Texture& wallpaperTexture, sf::Sprite& wallpaperSprite, sf::Texture& logoTexture, sf::Sprite& logoSprite, sf::Sprite& shadowSprite) {
    // INITIALIZE MAIN WALLPAPER
    wallpaperTexture.loadFromFile("assets/wallpaper.png");
    wallpaperSprite.setTexture(wallpaperTexture);
    wallpaperSprite.setPosition(0, 0);

    // INITIALIZE LOGO
    logoTexture.loadFromFile("assets/logo.png");
    logoSprite.setTexture(logoTexture);
    logoSprite.setPosition(330, 165);
    logoSprite.setScale(0.5f, 0.5f);

    // INITIALIZE SHADOW LOGO
    shadowSprite.setTexture(logoTexture);
    shadowSprite.setColor(sf::Color(0, 0, 0, 200));
    shadowSprite.setPosition(logoSprite.getPosition().x + 10, logoSprite.getPosition().y + 10);
    shadowSprite.setScale(0.5f, 0.5f); // Adjust the shadow size to match the logo
}

void handleMainMenu(sf::RenderWindow& window, sf::Sprite& wallpaperSprite, sf::Sprite& logoSprite, sf::Sprite& shadowSprite) {
    // BOOLEAN TO DETERMINE IF MOUSE ON TOP OF LOGO
    bool mouseOnButton = false;
    bool buttonPressed = false;

    // MAIN GAME RUNTIME
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { // IF USER CLICKS CLOSE EXECUTES window.close()
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed && mouseOnButton) {
                if (mouseOnButton) {
                    buttonPressed = true;
                    logoSprite.setColor(sf::Color(255, 255, 255, 255));
                    if (mouseOnButton && !buttonPressed) {
                        logoSprite.setColor(sf::Color(200, 200, 200, 255));
                    }
                    else if (!mouseOnButton && !buttonPressed) {
                        logoSprite.setColor(sf::Color(255, 255, 255, 255));
                    }

                    // DEPLOY GAME MODE MENU
                    std::cout << "hola" << std::endl;
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased) {
                buttonPressed = false;
                logoSprite.setColor(sf::Color(255, 255, 255, 255));
            }
        }


        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        mouseOnButton = logoSprite.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        if (mouseOnButton && !buttonPressed) {
            logoSprite.setColor(sf::Color(200, 200, 200, 255));
        }
        else if (!mouseOnButton && !buttonPressed) {
            logoSprite.setColor(sf::Color(255, 255, 255, 255));
        }

        window.clear();
        window.draw(wallpaperSprite);
        window.draw(shadowSprite); // Draw the shadow first
        window.draw(logoSprite);
        window.display();

        window.clear();
    }
}
