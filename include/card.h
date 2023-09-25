#ifndef CARD_H
#define CARD_H

#include <SFML/Graphics.hpp> // Include the SFML library for graphics

class Card {
public:
    // Constructor to initialize a card with a given color and number
    Card(const std::string& color, int number);

    // Function to set the card's texture based on its color and number
    void setTexture();

    // Function to get the card's texture
    sf::Texture& getTexture();

    // Function to get the card's number
    int getNumber() const;

    // Function to get the card's color
    std::string getColor() const;

    // Copy assignment operator
    Card& operator=(const Card& other);

private:
    sf::Texture texture; // Texture for the card
    std::string color;   // Color of the card
    int number;          // Number of the card
};

#endif
