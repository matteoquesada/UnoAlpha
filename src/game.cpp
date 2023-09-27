#include "../include/game.h"
#include <iostream>

using namespace sf;


//Deck deck;
//OTHER DECK
//OTHER OTHER DECK

Texture wallpaperTexture;
Sprite wallpaperSprite;
Texture wallpaperGameModeTexture;
Sprite wallpaperGameModeSprite;
Texture wallpaperInGameTexture;
Sprite wallpaperInGameSprite;
Texture logoTexture;
Sprite logoSprite;
Sprite shadowSprite;
Texture buttonPVPTexture;
Sprite buttonPVPSprite;
Texture buttonPVETexture;
Sprite buttonPVESprite;
SoundBuffer clickSoundBuffer;
Sound clickSound;
SoundBuffer clickLogoSoundBuffer;
Sound clickLogoSound;

// CONSTRACTOR TO INITIALIZE THE GAME OBJECT AND SHUFFLE THE DECK
Game::Game() : currentDisplay(0) {
	initializeResources();
	//deck.fillDeck();
	//deck.shuffle();
}

// FUNCTION TO INITIALIZE TEXTURES AND SPRITES -how to:-(TEXTURE, SPRITE, FILENAME, X, Y, SCALEX, SCALEY)
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

// FUNCTION TO INITIALIZE ALL RESOURCES USING THE FUNCTIONS ABOVE
void Game::initializeResources() {
	initializeTextureAndSprite(wallpaperTexture, wallpaperSprite, "assets/wallpaper.png", 0, 0);
	initializeTextureAndSprite(wallpaperGameModeTexture, wallpaperGameModeSprite, "assets/wallpaperGameMode.png", 0, 0);
	initializeTextureAndSprite(wallpaperInGameTexture, wallpaperInGameSprite, "assets/wallpaperInGame.png", 0, 0);
	initializeTextureAndSprite(logoTexture, logoSprite, "assets/logo.png", 330, 165, 0.5f, 0.5f);
	initializeTextureAndSprite(buttonPVPTexture, buttonPVPSprite, "assets/buttonPVP.png", 380, 165);
	initializeTextureAndSprite(buttonPVETexture, buttonPVESprite, "assets/buttonPVE.png", 380, 500);
	initializeSound(clickSound, clickSoundBuffer, "assets/sounds/clickPop.mp3");
	initializeSound(clickLogoSound, clickLogoSoundBuffer, "assets/sounds/clickLogo.mp3");
}

// FUNCTION TO RUN THE GAME USED IN THE MAIN FUNCTION
// USES CURRENT DISPLAY VARIABLE TO KEEP TRACK OF THE CURRENT DISPLAY AND CALLS THE CORRESPONDING FUNCTION
void Game::run(RenderWindow& window) {
	std::cout << "Game instance started successfully... Displaying window." << std::endl;

	while (window.isOpen()) {
		std:: cout << "estamos aqui main" << std::endl;
		switch (currentDisplay) {
		case 0:
			handleMainMenu(window);
			break;
		case 1:
			handleGameModeMenu(window);
			break;
		case 3:
			handleInGamePVE(window);
			break;
		}
	}
}

// FUNCTION TO HANDLE THE MAIN MENU INSIDE THE GAME LOOP
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

// FUNCTION TO HANDLE THE GAME MODE MENU INSIDE THE GAME LOOP
void Game::handleGameModeMenu(RenderWindow& window) {
	bool mouseOnButtonPVP = false;
	bool mouseOnButtonPVE = false;
	Vector2i mousePos = Mouse::getPosition(window);
	mouseOnButtonPVP = buttonPVPSprite.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
	mouseOnButtonPVE = buttonPVESprite.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
	static bool buttonClicked = false;
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
			if (mouseOnButtonPVP) {
				clickSound.play();
				buttonPVPSprite.setColor(Color(100, 100, 100, 255));
				std::cout << "Button PVP pressed" << std::endl;
				buttonClicked = true;
				currentDisplay = 2;
			}
			else if (mouseOnButtonPVE) {
				buttonPVESprite.setColor(Color(100, 100, 100, 255));
				std::cout << "Button PVE pressed" << std::endl;
				buttonClicked = true;
				currentDisplay = 3;
			}
		}
		else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
			if (buttonClicked) {
				buttonClicked = false;
			}
		}
	}
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
	window.clear();
	window.draw(wallpaperGameModeSprite);
	window.draw(buttonPVPSprite);
	window.draw(buttonPVESprite);
	window.display();
}



// FUNCTION TO HANDLE THE IN GAME PVE INSIDE THE GAME LOOP
void Game::handleInGamePVE(RenderWindow& window) {
	// Create the game instance

	Deck mainDeck;
	mainDeck.fillDeck();
	mainDeck.shuffle();

	// Create player and entity instances
	Player player;
	Player entity;

	// Draw initial hands for the player and entity
	player.drawInitialHand(mainDeck, 7); // Draw 10 cards for the player
	entity.drawInitialHand(mainDeck, 7); // Draw 10 cards for the entity

	bool gameOver = false;

	// Start the game loop
	while (window.isOpen() && !gameOver) {
		// Handle user input (e.g., playing cards, quitting the game

		// Render the game
		window.clear();
		window.draw(wallpaperInGameSprite);
		player.handleHand(window, 22., 600, true); // Display the player's hand
		entity.handleHand(window, 22.0, 7.0, false); // DISPLAY THE ENTITY'S HAND (OFFSET BY 22.0, 7.0) ->AND SCALE BY 0.5 BY DEFAULT<-
		mainDeck.displayDeck(window, 22.0, 40.0); // Display the main deck
		window.display();

		// For now, we'll exit the game loop after a certain condition (just for testing)
		if (player.getHandSize() == 1) {
			gameOver = true;
		}
	}
	// Game over logic (e.g., display a win/lose message, return to the main menu, etc.)
}

