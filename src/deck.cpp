#include <SFML/Graphics.hpp>
#include "../include/card.h" // Include your Card class header

// Define the Deck class to manage a collection of cards
class Deck {
public:
    // Constructor to initialize the deck
    Deck();

    // Function to shuffle the deck
    void shuffle();

    // Function to draw and remove the top card from the deck
    Card drawCard();

    // Function to display the entire deck on the window
    void displayDeck(sf::RenderWindow& window);

private:
    std::vector<Card> cards; // A vector to store the cards in the deck
};

// Deck constructor
Deck::Deck() {
    // Create a deck with all the cards you need
    for (int number = 0; number <= 9; ++number) {
        for (std::string color : { "red", "yellow", "green", "blue" }) {
            cards.push_back(Card(color, number));
        }
    }
}

// Shuffle the deck
void Deck::shuffle() {
    // Use a random algorithm to shuffle the deck (you can implement this)
    // For simplicity, you can use std::shuffle with a random engine.
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
        //return Card("empty", -1); // You can create a special "empty" card
    }
}

// Display the entire deck on the window
void Deck::displayDeck(sf::RenderWindow& window) {
    float xOffset = 10.0f;
    float yOffset = 10.0f;
    float cardSpacing = 10.0f;

    for (Card& card : cards) {
        sf::Sprite cardSprite;
        cardSprite.setTexture(card.getTexture());
        cardSprite.setPosition(xOffset, yOffset);
        window.draw(cardSprite);

        xOffset += card.getTexture().getSize().x + cardSpacing;
    }
}

