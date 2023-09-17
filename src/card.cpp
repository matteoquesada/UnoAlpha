#include "../include/card.h"

UNOCard::UNOCard(const char* color, int number) : color(color), number(number) {
    setTexture();
}

void UNOCard::setTexture() {
    // Construct the texture filename based on color and number
    char filename[50]; // Assuming a reasonable max filename length
    snprintf(filename, sizeof(filename), "assets/cards/%s%d.png", color, number);

    // Load and assign the texture
    if (texture.loadFromFile(filename)) {
        // Optionally, set the texture for sprite or render as needed
    }
}

sf::Texture& UNOCard::getTexture() {
    return texture;
}
