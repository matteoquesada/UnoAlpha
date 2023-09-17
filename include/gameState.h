// GameState.h
#pragma once

#include <SFML/Graphics.hpp>

class GameState {




public:
    // Enumeration to represent different game states
    enum class State {
        MainMenu,
        GameModeMenu,
        Gameplay,
    };

    // Constructor to initialize the game state
    GameState();

    // Function to update the game state
    void update(sf::RenderWindow& window);

    // Function to handle rendering
    void render(sf::RenderWindow& window);

    // Function to handle input
    void handleInput(sf::Event event);










private:
    State currentState;

    // Member variables for resources
    sf::Texture wallpaperTexture;
    sf::Sprite wallpaperSprite;
    sf::Texture logoTexture;
    sf::Sprite logoSprite;
    sf::Sprite shadowSprite;

    // Private function to initialize resources
    void initializeResources();

    // Member variables for button
    bool buttonHovered;
    bool buttonPressed;
    sf::Color buttonNormalColor;
    sf::Color buttonHoverColor;
};
