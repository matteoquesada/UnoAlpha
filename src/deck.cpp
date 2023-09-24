#include <SFML/Graphics.hpp>
#include "../include/card.h" // Include your Card class header
#include "../include/deck.h" // Include your Deck class header
#include <iostream>
#include <random>
using namespace sf;

// Define the Deck class to manage a collection of cards


// Deck constructor
// Deck constructor
Deck::Deck() {
    // Initialize the main deck with all cards, including special ones
    const int numColors = 4; // Red, Blue, Yellow, Green
    const int numNumbers = 10; // 0-9 number of numbers

    for (int colorIndex = 0; colorIndex < numColors; ++colorIndex) {
        std::string color;

        switch (colorIndex) {
        case 0:
            color = "red";
            break;
        case 1:
            color = "blue";
            break;
        case 2:
            color = "yellow";
            break;
        case 3:
            color = "green";
            break;
        default:
            color = "COLOR INPUT ERROR"; // Default to red for unsupported colors
        }

        for (int number = 0; number < numNumbers; ++number) {
            cards.emplace_back(color, number); // Add the card to the main deck
            cards.emplace_back(color, number); // Add another card of the same color and number
        }
    }

    // Add 4 of each special card to the main deck
    for (int i = 0; i < 4; ++i) {
        cards.emplace_back("special", -1); // specialRumble.png
        cards.emplace_back("special", -2); // specialPlus.png
    }
}





// Shuffle the deck
void Deck::shuffle() {
}

// Draw and remove the top card from the deck
Card Deck::drawCard() {
    if (!cards.empty()) {
        Card topCard = cards.back();
        cards.pop_back();
        return topCard;
    }
    else {
        // Handle the case when the deck is empty
        return Card("empty", -1); // You can create a special "empty" card
    }
}

// Display the entire deck on the window
void Deck::displayDeck(sf::RenderWindow& window) {
   // const float screenWidth = static_cast<float>(window.getSize().x);
    //const float screenHeight = static_cast<float>(window.getSize().y);

    const float cardWidth = cards[0].getTexture().getSize().x;
    const float cardHeight = cards[0].getTexture().getSize().y;

    // Calculate the initial position to center the pile horizontally
    float xOffset = 1200.0;

    // Calculate the initial position for the pile's top card
    float topYOffset = 0.0;

    // Define a spacing between cards in the pile
    const float cardSpacing = 10.0f;
    for (Card& card : cards) {
        Sprite cardSprite;
        cardSprite.setTexture(card.getTexture());
        cardSprite.setPosition(xOffset, topYOffset);

        window.draw(cardSprite);

        // Increase the Y offset for the next card
        topYOffset += cardSpacing;
    }
}





