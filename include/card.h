#pragma once
#include <SFML/Graphics.hpp>

class Card {
public:
    Card(sf::Texture& texture);

private:
    sf::Sprite sprite;
    sf::Vector2f position;
    bool isMouseOnButton;
    bool buttonPressed;
    bool buttonClicked;
};


