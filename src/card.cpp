#include "../include/card.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace sf;
// bradley added this   constructor 
// Constructor to initialize a card with a given color and number
Card::Card(const std::string& color, int number) : color(color), number(number) {
    setTexture(); // Set the card's texture based on color and number
}

// Function to set the card's texture based on its color and number
void Card::setTexture() {
    // Construct the texture filename based on color and number
    std::string filename = "assets/cards/";
    //std::cout<<"color: "<<color<<std::endl;
    // Convert the color to a lowercase string for the filename
    if (color == "red") {
        filename += "red";
    }
    else if (color == "yellow") {
        filename += "yellow";
    }
    else if (color == "green") {
        filename += "green";
    }
    else if (color == "blue") {
        filename += "blue";
    }
    else {
        // Handle unsupported colors (default to red)
        filename += "white";
    }

    // Add the number to the filename
    filename += std::to_string(number);
    filename += ".png";
    std::cout<<"filename: "<<filename<<std::endl;
    // Load and assign the texture
    if (texture.loadFromFile(filename)) {
        // Optionally, set the texture for a sprite or render as needed
    }
}

// Function to get the card's texture
sf::Texture& Card::getTexture() {
    return texture;
}

// Function to get the card's number
int Card::getNumber() const {
    return number;
}

// Function to get the card's color
std::string Card::getColor() const {
    return color;
}
