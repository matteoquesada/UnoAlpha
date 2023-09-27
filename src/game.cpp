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
	mainDeck.fillDeck();
	mainDeck.shuffle();
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
	// CREATE A TURN VARIABLE TO KEEP TRACK OF THE CURRENT TURN
	int turn = 1;

	// CREATE A BOOLEAN VARIABLE TO KEEP TRACK OF THE GAME OVER STATE
	bool gameOver = false;

	// CREATE A DECK OBJECT AND FILL IT WITH CARDS AND SHUFFLE IT

	Deck stashDeck;


	// CREATE A PLAYER OBJECT AND AN ENTITY OBJECT IN ORDER TO PLAY THE GAME
	Player player;
	Player entity;

	// DRAW 7 CARDS FOR THE PLAYER AND THE ENTITY
	player.drawInitialHand(mainDeck, 7);
	entity.drawInitialHand(mainDeck, 7);

	// START THE GAME LOOP
	while (window.isOpen() && !gameOver) {
		//std::cout << "Current turn: " << turn << std::endl;	
		// CHECK IF THE PLAYER'S TURN IS OVER
		if (turn % 2 == 0) {
			window.clear();
			window.draw(wallpaperInGameSprite);
			player.handleHand(window, false, turn, player.getHand(), entity.getHand(), stashDeck, mainDeck); // DISPLAY THE PLAYER'S HAND AS NOT CONTROLLABLE (OFFSET BY 22.0, 7.0) ->AND SCALE BY 0.5 BY DEFAULT<-
			entity.handleHand(window, true, turn, entity.getHand(), player.getHand(), stashDeck, mainDeck); // DISPLAY THE ENTITY'S HAND AS CONTROLLABLE

			
		}
		else {
			window.clear();
			window.draw(wallpaperInGameSprite);
			player.handleHand(window, true, turn, player.getHand(), entity.getHand(), stashDeck, mainDeck); // DISPLAY THE PLAYER'S HAND AS CONTROLLABLE
			entity.handleHand(window, false, turn, entity.getHand(), player.getHand(), stashDeck, mainDeck); // DISPLAY THE ENTITY'S HAND AS NOT CONTROLLABLE (OFFSET BY 22.0, 7.0) ->AND SCALE BY 0.5 BY DEFAULT<-
		}

		// DISPLAY THE MAIN DECK AS DEBUG 
		//mainDeck.displayDeck(window, 22.0, 90.0); // Display the main deck

		// DISPLAY THE MAIN WINDOW
		window.display();

		// GAME OVER LOGIC (CURRENTLY ONLY CHECKS IF THE PLAYER'S HAND IS EMPTY)
		if (player.getHandSize() == 1) {
			gameOver = true;
		}
	}
	// GAME OVER SCREEN
	window.clear();
}

void Game::HandleInGamePVP(sf::RenderWindow& window) {
	// CREATE A TURN VARIABLE TO KEEP TRACK OF THE CURRENT TURN
	int turn = 1;

	// CREATE A BOOLEAN VARIABLE TO KEEP TRACK OF THE GAME OVER STATE
	bool gameOver = false;

	// CREATE A DECK OBJECT AND FILL IT WITH CARDS AND SHUFFLE IT

	

	Deck stashDeck;
	stashDeck.initializeStash(mainDeck);

	// CREATE A PLAYER OBJECT AND AN ENTITY OBJECT IN ORDER TO PLAY THE GAME
	Player player;
	Player entity;

	// DRAW 7 CARDS FOR THE PLAYER AND THE ENTITY
	player.drawInitialHand(mainDeck, 7);
	entity.drawInitialHand(mainDeck, 7);

	// START THE GAME LOOP
	while (window.isOpen() && !gameOver) {
		//std::cout << "Current turn: " << turn << std::endl;	
		// CHECK IF THE PLAYER'S TURN IS OVER
		if (turn % 2 == 0) {
			window.clear();
			window.draw(wallpaperInGameSprite);
			player.handleHand(window, false, turn, player.getHand(), entity.getHand(), stashDeck, mainDeck); // DISPLAY THE PLAYER'S HAND AS NOT CONTROLLABLE (OFFSET BY 22.0, 7.0) ->AND SCALE BY 0.5 BY DEFAULT<-
			entity.handleHand(window, true, turn, entity.getHand(), player.getHand(), stashDeck, mainDeck); // DISPLAY THE ENTITY'S HAND AS CONTROLLABLE


		}
		else {
			window.clear();
			window.draw(wallpaperInGameSprite);
			player.handleHand(window, true, turn, player.getHand(), entity.getHand(), stashDeck, mainDeck); // DISPLAY THE PLAYER'S HAND AS CONTROLLABLE
			entity.handleHand(window, false, turn, entity.getHand(), player.getHand(), stashDeck, mainDeck); // DISPLAY THE ENTITY'S HAND AS NOT CONTROLLABLE (OFFSET BY 22.0, 7.0) ->AND SCALE BY 0.5 BY DEFAULT<-
		}

		// DISPLAY THE MAIN DECK AS DEBUG 
		//mainDeck.displayDeck(window, 22.0, 90.0); // Display the main deck

		// DISPLAY THE MAIN WINDOW
		window.display();

		// GAME OVER LOGIC (CURRENTLY ONLY CHECKS IF THE PLAYER'S HAND IS EMPTY)
		if (player.getHandSize() == 1) {
			gameOver = true;
		}
	}
	// GAME OVER SCREEN
	window.clear();
}

