#pragma once
#include <SFML/Graphics.hpp>

void initializeMainMenuResources(sf::Texture& wallpaperTexture, sf::Sprite& wallpaperSprite, sf::Texture& logoTexture, sf::Sprite& logoSprite, sf::Sprite& shadowSprite);

void handleMainMenu(sf::RenderWindow& window, sf::Sprite& wallpaperSprite, sf::Sprite& logoSprite, sf::Sprite& shadowSprite);
