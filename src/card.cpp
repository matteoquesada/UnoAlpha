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
        std::cout << "FAILED TO LOAD IMAGE \"" << filename << "\". REASON: UNABLE TO OPEN FILE" << std::endl;
    }
}

// GET THE TEXTURE OF THE CARD
sf::Texture& Card::getTexture() {
    return texture;
}

// GET THE BACK FACE TEXTURE OF THE CARD
sf::Texture& Card::getBackTexture() {
    static sf::Texture backTexture; // MAKE IT STATIC TO LOAD ONLY ONCE
    if (backTexture.getSize().x == 0) { // CHECK IF IT'S NOT LOADED YET
        backTexture.loadFromFile("assets/cards/backFace.png");
    }
    return backTexture;
}

// GET THE NUMBER OF THE CARD
int Card::getNumber() const {
    return number;
}

// GET THE COLOR OF THE CARD
std::string Card::getColor() const {
    return color;
}

// GET THE TYPE OF THE CARD
std::string Card::getType() const {
    return type;
}

// ASSIGNMENT OPERATOR
Card& Card::operator=(const Card& other) {
    if (this != &other) {
        color = other.color;
        number = other.number;
        texture = other.texture; // ASSUMING SF::TEXTURE SUPPORTS ASSIGNMENT
    }
    return *this;
}

// GET THE SIZE OF THE CARD
sf::Vector2u Card::getSize() const {
    return texture.getSize();
}

// CHECK IF THE CARD IS A WILD CARD
bool Card::isWild() {
    return number == -5 || number == -4;
}
// CHECK IF THE CARD IS A SPECIAL CARD
bool Card::isSpecial() {
    return number == -1 || number == -2 || number == -3;
}
// SET THE COLOR OF THE CARD
void Card::setColor(const std::string& newColor) {
    color = newColor;
}
