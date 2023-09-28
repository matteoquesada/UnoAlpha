#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;
#include "player.h"
#include "deck.h"
#include "card.h"

class Game {
public:
    // CONSTRUCTOR
    Game();

    // MAIN GAME LOOP FUNCTION
    void run(sf::RenderWindow& window);

private:
    // MAIN DECK OF CARDS
    Deck mainDeck;

    // STASH DECK
    Deck stashDeck;

    // INTEGER TO KEEP TRACK OF THE CURRENT DISPLAY
    int currentDisplay;

    // FUNCTION TO INITIALIZE ALL RESOURCES
    void initializeResources();

    // FUNCTION TO INITIALIZE TEXTURES AND SPRITES
    void initializeTextureAndSprite(sf::Texture& texture, sf::Sprite& sprite, const std::string& textureFile, float x, float y, float scaleX = 1.0f, float scaleY = 1.0f);

    // FUNCTION TO INITIALIZE SOUNDS
    void initializeSound(sf::Sound& sound, sf::SoundBuffer& soundBuffer, const std::string& soundFile);

    // FUNCTION TO HANDLE THE MAIN MENU
    void handleMainMenu(sf::RenderWindow& window);

    // FUNCTION TO HANDLE THE GAME MODE MENU
    void handleGameModeMenu(sf::RenderWindow& window);

    // FUNCTION TO HANDLE THE IN-GAME PVE MODE
    void handleInGamePVE(sf::RenderWindow& window);

    // FUNCTION TO HANDLE THE IN-GAME PVP MODE
    void HandleInGamePVP(sf::RenderWindow& window);

    // FUNCTION TO HANDLE THE DRAW BUTTON DEPENDING ON THE CURRENT TURN
    void handleDrawButton(sf::RenderWindow& window, Player& currentPlayer, Deck& mainDeck, int turn);

    // FUNCTION TO CHECK IF UNO BUTTON SHOULD BE DISPLAYED
    bool isUnoButton(sf::RenderWindow& window, Deck& playerHand);

    // FUNCTION TO HANDLE THE UNO BUTTON
    void handleUnoButton(sf::RenderWindow& window, Deck& playerDeck, bool isButtonAvailable, bool& isGameOver);

    // BOOLEAN VARIABLE TO KEEP TRACK OF THE GAME OVER STATE
    bool gameOver;
};
