#include "../include/card.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace sf;

// CONSTRUCTOR TO INITIALIZE A CARD WITH A GIVEN COLOR AND NUMBER
Card::Card(const std::string& color, int number) : color(color), number(number) {
    // INITIALIZE THE CARD'S COLOR AND NUMBER DEPENDING ON THE PARAMETERS PASSED TO THE CONSTRUCTOR
    // SPECIAL CARDS HAVE A NEGATIVE NUMBER IN ORDER TO BE DIFFERENTIATED FROM THE COMMON CARDS
    // THE NEGATIVE NUMBER IS USED TO DETERMINE THE TYPE OF THE SPECIAL CARD
    // THE TYPE OF THE SPECIAL CARD IS USED TO CONSTRUCT THE FILENAME OF THE TEXTURE AND DIFFERENTIATE IT FROM THE COMMON CARDS (DEFAULT CASE)
    switch (number) {
    case -1: type = "Reverse"; break;
    case -2: type = "Plus2"; break;
    case -3: type = "Skip"; break;
    case -4: type = "Plus4"; break;
    case -5: type = "Rumble"; break;
    default: type = "Common"; break;
    }
    setCardTexture(); // SET THE CARD'S TEXTURE BASED ON ITS COLOR AND NUMBER OR TYPE IF != "Common"
}




// FUNCTION TO SET THE CARD'S TEXTURE BASED ON ITS COLOR AND NUMBER OR TYPE IF != "Common"
void Card::setCardTexture() {
    // CONSTRUCT THE FILENAME OF THE TEXTURE BASED ON THE CARD'S COLOR AND NUMBER OR TYPE IF != "Common"
    // BY CONCATENATING THE COLOR AND NUMBER OR TYPE IF != "Common" TO THE FILENAME OF THE TEXTURE
    std::string filename = "assets/cards/";
    filename += color;

    if (type != "Common") {
        filename += type;
    }
    else {
        filename += std::to_string(number);
    }

    filename += ".png";

    // LOAD THE TEXTURE FROM THE FILENAME AND PRINT A MESSAGE TO THE CONSOLE IF THE TEXTURE WAS LOADED SUCCESSFULLY OR NOT
    if (texture.loadFromFile(filename)) {
        std::cout << "Loaded texture from directory: " << filename << std::endl;
    }
    else {
        std::cout << "Failed to load image \"" << filename << "\". Reason: Unable to open file" << std::endl;
    }
}

// FUNCTION TO GET THE CARD'S TEXTURE
sf::Texture& Card::getTexture() {
    return texture;
}

// FUNCTION TO GET THE CARD'S BACK TEXTURE (WORKS THE SAME FOR ALL CARDS)
sf::Texture& Card::getBackTexture() {
    backTexture.loadFromFile("assets/cards/backFace.png");
    return backTexture;
}

// Function to get the card's number
int Card::getNumber() const {
    return number;
}

// Function to get the card's color
std::string Card::getColor() const {
    return color;
}

std::string Card::getType() const {
    return type;
}

// Copy assignment operator implementation
Card& Card::operator=(const Card& other) {
    if (this != &other) {
        // Copy each member variable from 'other' to 'this'
        this->color = other.color;
        this->number = other.number;
        // Copy other members as needed
        this->texture = other.texture; // Copy texture (assuming sf::Texture supports assignment)
    }
    return *this;
}

sf::Vector2u Card::getSize() const {
    return texture.getSize();
}

// Function to perform a card action
void Card::action() {
    // Perform the card's action
    // ...
}

// Function to check if the card is a special card
bool Card::isSpecial() const {
    return number < 0;
}