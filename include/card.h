#ifndef UNOCARD_H
#define UNOCARD_H

#include <SFML/Graphics.hpp>

class UNOCard {
public:
    // Constructor to initialize the card with a given color and number
    UNOCard(const char* color, int number);

    // Function to set the card's texture based on color and number
    void setTexture();

    // Function to get the card's texture
    sf::Texture& getTexture();

private:
    sf::Texture texture;
    const char* color;
    int number;
};

#endif // UNOCARD_H
