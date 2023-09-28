#include "../include/game.h"
#include <iostream>
#include "../include/deck.h"

using namespace sf;

// GLOBAL TEXTURES, SPRITES, AND SOUNDS
Texture wallpaperTexture;
Sprite wallpaperSprite;
Texture wallpaperGameModeTexture;
Sprite wallpaperGameModeSprite;
Texture wallpaperInGameTexture;
Sprite wallpaperInGameSprite;
Texture logoTexture;
Sprite logoSprite;
Texture buttonPVPTexture;
Sprite buttonPVPSprite;
Texture buttonPVETexture;
Sprite buttonPVESprite;
Texture drawButtonTexture;
Sprite drawButtonSprite;
Sprite unoButtonSprite;
SoundBuffer clickSoundBuffer;
Sound clickSound;
SoundBuffer clickLogoSoundBuffer;
Sound clickLogoSound;

// GAME CONSTRUCTOR: INITIALIZES THE GAME OBJECT AND RESOURCES
Game::Game() : currentDisplay(0) {
    initializeResources();
}

// FUNCTION TO INITIALIZE TEXTURES AND SPRITES
void Game::initializeTextureAndSprite(Texture& texture, Sprite& sprite, const std::string& textureFile, float x, float y, float scaleX, float scaleY) {
    texture.loadFromFile(textureFile);
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    sprite.setScale(scaleX, scaleY);
}

// FUNCTION TO INITIALIZE SOUNDS
void Game::initializeSound(Sound& sound, SoundBuffer& soundBuffer, const std::string& soundFile) {
    soundBuffer.loadFromFile(soundFile);
    sound.setBuffer(soundBuffer);
}

// FUNCTION TO INITIALIZE ALL RESOURCES
void Game::initializeResources() {
    initializeTextureAndSprite(wallpaperTexture, wallpaperSprite, "assets/wallpaper.png", 0, 0);
    initializeTextureAndSprite(wallpaperGameModeTexture, wallpaperGameModeSprite, "assets/wallpaperGameMode.png", 0, 0);
    initializeTextureAndSprite(wallpaperInGameTexture, wallpaperInGameSprite, "assets/wallpaperInGame.png", 0, 0);
    initializeTextureAndSprite(logoTexture, logoSprite, "assets/logo.png", 330, 165, 0.5f, 0.5f);
    initializeTextureAndSprite(buttonPVPTexture, buttonPVPSprite, "assets/buttonPVP.png", 380, 165);
    initializeTextureAndSprite(buttonPVETexture, buttonPVESprite, "assets/buttonPVE.png", 380, 500);
    initializeTextureAndSprite(drawButtonTexture, drawButtonSprite, "assets/drawCard.png", 1165, 610, 0.2f, 0.2f);
    initializeTextureAndSprite(logoTexture, unoButtonSprite, "assets/logo.png", 1020, 618, 0.1f, 0.1f);
    initializeSound(clickSound, clickSoundBuffer, "assets/sounds/clickPop.mp3");
    initializeSound(clickLogoSound, clickLogoSoundBuffer, "assets/sounds/clickLogo.mp3");
}

// MAIN GAME LOOP: HANDLES THE GAME'S MAIN LOGIC
void Game::run(RenderWindow& window) {
    mainDeck.fillDeck();
    mainDeck.shuffle();
    stashDeck.initializeStash(mainDeck);
    std::cout << "Stash size: " << stashDeck.getSize() << std::endl;
    std::cout << "Game instance started successfully... Displaying window." << std::endl;

    while (window.isOpen()) {
        switch (currentDisplay) {
        case 0:
            handleMainMenu(window);
            break;
        case 1:
            handleGameModeMenu(window);
            break;
        case 2:
            HandleInGamePVP(window);
            break;
        case 3:
            handleInGamePVE(window);
            break;
        }
    }
}

// FUNCTION TO HANDLE THE MAIN MENU
void Game::handleMainMenu(RenderWindow& window) {
    bool mouseOnButton = false;
    bool buttonPressed = false;
    Event event;
    Vector2i mousePos = Mouse::getPosition(window);
    mouseOnButton = logoSprite.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    static bool buttonClicked = false;
    while (window.pollEvent(event)) {
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            buttonPressed = true;
        }
        else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
            buttonPressed = false;
            if (mouseOnButton && buttonClicked) {
                clickLogoSound.play();
                std::cout << "Button pressed" << std::endl;
                logoSprite.setColor(Color(150, 150, 150, 255));
                currentDisplay = 1;
            }
            buttonClicked = false;
        }
    }
    if (mouseOnButton && !buttonPressed) {
        logoSprite.setColor(Color(200, 200, 200, 255));
        buttonClicked = true;
    }
    else if (!mouseOnButton && !buttonPressed) {
        logoSprite.setColor(Color(255, 255, 255, 255));
    }
    window.clear();
    window.draw(wallpaperSprite);
    window.draw(logoSprite);
    //deck.displayDeck(window);
    window.display();
}

// FUNCTION TO HANDLE THE GAME MODE MENU
void Game::handleGameModeMenu(RenderWindow& window) {
    // CREATE A BOOLEAN VARIABLE TO KEEP TRACK OF THE MOUSE POSITION ON THE BUTTONS (BECAUSE THE BUTTONS ARE SEPARATE SPRITES)
    bool mouseOnButtonPVP = false;
    bool mouseOnButtonPVE = false;
    Vector2i mousePos = Mouse::getPosition(window);
    mouseOnButtonPVP = buttonPVPSprite.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    mouseOnButtonPVE = buttonPVESprite.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    static bool buttonClicked = false; // CREATE A BOOLEAN VARIABLE TO KEEP TRACK OF THE BUTTON CLICKS -STATIC BECAUSE IT NEEDS TO KEEP ITS VALUE BETWEEN FUNCTION CALLS-

    Event event;
    while (window.pollEvent(event)) {

        // CHECK IF THE MOUSE IS ON THE BUTTONS AND IF THE MOUSE BUTTON IS PRESSED
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            if (mouseOnButtonPVP) {
                clickSound.play();
                buttonPVPSprite.setColor(Color(100, 100, 100, 255));
                std::cout << "Button PVP pressed" << std::endl;
                buttonClicked = true;
                currentDisplay = 2;
            }
            else if (mouseOnButtonPVE) {
                clickSound.play();
                buttonPVESprite.setColor(Color(100, 100, 100, 255));
                std::cout << "Button PVE pressed" << std::endl;
                buttonClicked = true;
                currentDisplay = 3;
            }
        }
        // CHECK IF THE MOUSE BUTTON IS RELEASED
        else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
            // CHECK IF THE BUTTON WAS CLICKED AND THEN RESET THE BUTTON CLICKED VARIABLE IN ORDER TO ALLOW THE BUTTON TO BE CLICKED AGAIN
            if (buttonClicked) {
                buttonClicked = false;
            }
        }
    }
    // CHECK IF THE MOUSE IS ON THE BUTTONS AND IF THE BUTTON WAS CLICKED
    // PURE COSMETIC CHANGES TO THE BUTTONS
    // NOT NECESSARY FOR THE GAME TO WORK
    if (mouseOnButtonPVP && !buttonClicked) {
        buttonPVPSprite.setColor(Color(200, 200, 200, 255));
    }
    else if (!mouseOnButtonPVP && !buttonClicked) {
        buttonPVPSprite.setColor(Color(255, 255, 255, 255));
    }
    if (mouseOnButtonPVE && !buttonClicked) {
        buttonPVESprite.setColor(Color(200, 200, 200, 255));
    }
    else if (!mouseOnButtonPVE && !buttonClicked) {
        buttonPVESprite.setColor(Color(255, 255, 255, 255));
    }

    // DRAW THE BUTTONS AND THE WALLPAPER
    window.clear();
    window.draw(wallpaperGameModeSprite);
    window.draw(buttonPVPSprite);
    window.draw(buttonPVESprite);
    window.display();
}

// FUNCTION TO HANDLE THE IN-GAME PVE MODE (CURRENTLY IS NOT WORKING AND WORKS THE SAME AS THE PVP MODE)
void Game::handleInGamePVE(RenderWindow& window) {
    // CREATE A TURN VARIABLE TO KEEP TRACK OF THE CURRENT TURN
    int turn = 1;

    // CREATE A BOOLEAN VARIABLE TO KEEP TRACK OF THE GAME OVER STATE
    bool gameOver = false;

    // CREATE A PLAYER OBJECT AND AN ENTITY OBJECT IN ORDER TO PLAY THE GAME
    Player player;
    Player player2;

    // DRAW 7 CARDS FOR THE PLAYER AND THE ENTITY
    player.drawInitialHand(mainDeck, 7);
    player2.drawInitialHand(mainDeck, 7);

    // START THE BASE GAME ENGINE LOOP
    while (window.isOpen() && !gameOver) {
        // ENGINE LOGIC FOR SECOND PLAYER
        if (turn % 2 == 0) {
            window.clear();
            window.draw(wallpaperInGameSprite);
            handleUnoButton(window, player2.getHand(), isUnoButton(window, player2.getHand()), gameOver);
            handleDrawButton(window, player2, mainDeck, turn);
            player.handleHand(window, false, turn, player.getHand(), player2.getHand(), stashDeck, mainDeck); // DISPLAY THE PLAYER'S HAND AS NOT CONTROLLABLE (OFFSET BY 22.0, 7.0) ->AND SCALE BY 0.5 BY DEFAULT<-
            player2.handleHand(window, true, turn, player2.getHand(), player.getHand(), stashDeck, mainDeck); // DISPLAY THE ENTITY'S HAND AS CONTROLLABLE
        }
        // ENGINE LOGIC FOR FIRST PLAYER
        else {
            window.clear();
            window.draw(wallpaperInGameSprite);
            handleUnoButton(window, player.getHand(), isUnoButton(window, player.getHand()), gameOver);
            handleDrawButton(window, player, mainDeck, turn);
            player.handleHand(window, true, turn, player.getHand(), player2.getHand(), stashDeck, mainDeck); // DISPLAY THE PLAYER'S HAND AS CONTROLLABLE
            player2.handleHand(window, false, turn, player2.getHand(), player.getHand(), stashDeck, mainDeck); // DISPLAY THE ENTITY'S HAND AS NOT CONTROLLABLE (OFFSET BY 22.0, 7.0) ->AND SCALE BY 0.5 BY DEFAULT<-
        }

        // DISPLAY THE STASH IN THE MIDDLE OF THE SCREEN 
        stashDeck.displayDeck(window, 640.0, 360.0);
        window.display();
    }
    // GAME OVER SCREEN
    window.clear();
    currentDisplay = 1;
}

// FUNCTION TO HANDLE THE IN-GAME PVP MODE
void Game::HandleInGamePVP(sf::RenderWindow& window) {
    // CREATE A TURN VARIABLE TO KEEP TRACK OF THE CURRENT TURN
    int turn = 1;

    // CREATE A BOOLEAN VARIABLE TO KEEP TRACK OF THE GAME OVER STATE
    bool gameOver = false;

    // CREATE A PLAYER OBJECT AND AN ENTITY OBJECT IN ORDER TO PLAY THE GAME
    Player player;
    Player player2;

    // DRAW 7 CARDS FOR THE PLAYER AND THE ENTITY
    player.drawInitialHand(mainDeck, 7);
    player2.drawInitialHand(mainDeck, 7);

    // START THE BASE GAME ENGINE LOOP
    while (window.isOpen() && !gameOver) {
        // ENGINE LOGIC FOR SECOND PLAYER
        if (turn % 2 == 0) {
            window.clear();
            window.draw(wallpaperInGameSprite);
            handleUnoButton(window, player2.getHand(), isUnoButton(window, player2.getHand()), gameOver);
            handleDrawButton(window, player2, mainDeck, turn);
            player.handleHand(window, false, turn, player.getHand(), player2.getHand(), stashDeck, mainDeck); // DISPLAY THE PLAYER'S HAND AS NOT CONTROLLABLE (OFFSET BY 22.0, 7.0) ->AND SCALE BY 0.5 BY DEFAULT<-
            player2.handleHand(window, true, turn, player2.getHand(), player.getHand(), stashDeck, mainDeck); // DISPLAY THE ENTITY'S HAND AS CONTROLLABLE
        }
        // ENGINE LOGIC FOR FIRST PLAYER
        else {
            window.clear();
            window.draw(wallpaperInGameSprite);
            handleUnoButton(window, player.getHand(), isUnoButton(window, player.getHand()), gameOver);
            handleDrawButton(window, player, mainDeck, turn);
            player.handleHand(window, true, turn, player.getHand(), player2.getHand(), stashDeck, mainDeck); // DISPLAY THE PLAYER'S HAND AS CONTROLLABLE
            player2.handleHand(window, false, turn, player2.getHand(), player.getHand(), stashDeck, mainDeck); // DISPLAY THE ENTITY'S HAND AS NOT CONTROLLABLE (OFFSET BY 22.0, 7.0) ->AND SCALE BY 0.5 BY DEFAULT<-
        }

        // DISPLAY THE STASH IN THE MIDDLE OF THE SCREEN 
        stashDeck.displayDeck(window, 640.0, 360.0); 
        window.display();
    }
    // GAME OVER SCREEN
    window.clear();
    currentDisplay = 1;
}

// FUNCTION TO HANDLE THE DRAW BUTTON DEPENDING ON THE CURRENT TURN
void Game::handleDrawButton(sf::RenderWindow& window, Player& currentPlayer, Deck& mainDeck, int turn) {
    Event event{};
    Vector2i mousePos = Mouse::getPosition(window);
    bool mouseOnDrawButton = drawButtonSprite.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    bool buttonPressed = false;
    buttonPressed = event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left;

    // CHECKS IF THE MOUSE IS ON THE DRAW CARD BUTTON IN ORDER TO DRAW A CARD FROM THE MAIN DECK
    if (mouseOnDrawButton && currentPlayer.getHandSize() < 18) {
        drawButtonSprite.setColor(Color(200, 200, 200, 255));
        if (Mouse::isButtonPressed(Mouse::Left)) {
            std::cout << "Got a new card out of the pile! " << std::endl;
            sf::sleep(sf::seconds(1.0f));
            currentPlayer.drawCard(mainDeck);
        }
    }
    else {
        drawButtonSprite.setColor(Color(255, 255, 255, 255));
    }
    window.draw(drawButtonSprite);
}

bool Game::isUnoButton(sf::RenderWindow& window, Deck& playerHand) {
    if (playerHand.getSize() == 1) return true;
    else return false;
}
// FUNCTION TO HANDLE THE UNO BUTTON DEPENDING ON THE CURRENT TURN
void Game::handleUnoButton(sf::RenderWindow& window, Deck& playerDeck, bool isButtonAvailable, bool& isGameOver) {
    // CHECK IF THE PLAYER'S HAND SIZE IS EQUAL TO 1
    if (isButtonAvailable) {
        // TURNS THE UNO BUTON AT ITS NORMAL COLOR WHEN THE PLAYER'S HAND SIZE IS EQUAL TO 1
        unoButtonSprite.setColor(Color(255, 255, 255, 255));
        Event event{};
        Vector2i mousePos = Mouse::getPosition(window);
        bool mouseOnUnoButton = unoButtonSprite.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        bool buttonPressed = false;
        buttonPressed = event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left;
        // CHECK IF THE MOUSE IS ON THE UNO BUTTON
        if (mouseOnUnoButton) {
            // CHECK IF THE MOUSE BUTTON IS PRESSED
            if (Mouse::isButtonPressed(Mouse::Left)) {
                std::cout << "Button UNO pressed" << std::endl;
                sf::sleep(sf::seconds(1.0f));
                std::cout << "You said UNO!" << std::endl;
                isGameOver = true;
            }
        }
        // CHECKS IF THE MOUSE IS NOT ON THE UNNO BUTTON
        else {
            unoButtonSprite.setColor(Color(100, 100, 100, 255));
        }
        window.draw(unoButtonSprite);
    }
}
