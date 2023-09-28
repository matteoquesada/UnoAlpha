#include "../include/card.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace sf;

// CONSTRUCTOR: INITIALIZE A CARD WITH SPECIFIED COLOR AND NUMBER
Card::Card(const std::string& color, int number) : color(color), number(number) {
    // DETERMINE CARD TYPE BASED ON ITS NUMBER
    switch (number) {
    case -1: type = "Reverse"; break;
    case -2: type = "Plus2"; break;
    case -3: type = "Skip"; break;
    case -4: type = "Plus4"; break;
    case -5: type = "Rumble"; break;
    default: type = "Common"; break;
    }
    setCardTexture();
}

// SET THE CARD'S TEXTURE BASED ON ITS COLOR AND TYPE
void Card::setCardTexture() {
    std::string filename = "assets/cards/" + color + (type != "Common" ? type : std::to_string(number)) + ".png";

    if (!texture.loadFromFile(filename)) {
        std::cout << "Failed to load image \"" << filename << "\". Reason: Unable to open file" << std::endl;
    }
}

sf::Texture& Card::getTexture() {
    return texture;
}
// GET THE BACK FACE TEXTURE OF THE CARD (
sf::Texture& Card::getBackTexture() {
    static sf::Texture backTexture; // Make it static to load only once
    if (backTexture.getSize().x == 0) { // Check if it's not loaded yet
        backTexture.loadFromFile("assets/cards/backFace.png");
    }
    return backTexture;
}

int Card::getNumber() const {
    return number;
}

std::string Card::getColor() const {
    return color;
}

std::string Card::getType() const {
    return type;
}

Card& Card::operator=(const Card& other) {
    if (this != &other) {
        color = other.color;
        number = other.number;
        texture = other.texture; // Assuming sf::Texture supports assignment
    }
    return *this;
}

sf::Vector2u Card::getSize() const {
    return texture.getSize();
}

bool Card::isWild(){
    return number == -5 || number == -4;
}

void Card::setColor(const std::string& newColor) {
    color = newColor;
}
