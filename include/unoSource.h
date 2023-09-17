#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

void initializeMainMenuResources();

void handleMainMenu(RenderWindow& window, int& currentDisplay);

void handleGameModeMenu(RenderWindow& window, int& currentDisplay);

void handleInGamePVE(RenderWindow& window, int& currentDisplay);