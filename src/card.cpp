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
// Modify the Card class

// Function to set the card's texture based on its color and number
void Card::setTexture() {
    // Construct the texture filename based on color and number
    std::string filename = "assets/cards/";

    if (number == -1) {
        // Special card without a number
        filename += "specialRumble.png";
    }
    else if (number == -2) {
        // Another special card without a number
        filename += "specialPlus.png";
    }
    else {
        // Convert the color to a lowercase string for the filename
        if (color == "red") {
            filename += "red";
        }
        else if (color == "blue") {
            filename += "blue";
        }
        else if (color == "yellow") {
            filename += "yellow";
        }
        else if (color == "green") {
            filename += "green";
        }
        else {
            // Handle unsupported colors
            filename += "special";
        }

        // Add the number to the filename
        filename += std::to_string(number);
        filename += ".png";
    }

    // Load and assign the texture
    if (texture.loadFromFile(filename)) {
        // Optionally, set the texture for a sprite or render as needed
    }
    else {
        std::cout << "Failed to load image \"" << filename << "\". Reason: Unable to open file" << std::endl;
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

