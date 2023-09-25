#include <SFML/Graphics.hpp>
#include "../include/card.h" // Include your Card class header
#include "../include/deck.h" // Include your Deck class header
#include <iostream>
#include <random>
using namespace sf;

// DEFINE THE DECK CLASS TO MANAGE A COLLECTION OF CARDS
// DECK CONSTRUCTOR

Deck::Deck() {
    // INITIALIZE THE MAIN DECK WITH ALL CARDS, INCLUDING SPECIAL ONES
    std::string colors[4] = { "red", "blue", "yellow", "green" };

    int totalCards = 0; // INITIALIZE THE TOTAL NUMBER OF CARDS TO 0 (DEBUG)

    for (int i = 0; i < 4; i++) {
        for (int number = 0; number <= 10; ++number) {
            if (number == 0) {
                addCard(colors[i], number, 1); // Add one zero card to the main deck per color
            }
            else if (number == 10) {
                addSpecialCards(colors[i]);
                totalCards += 8; // INCREMENT THE COUNT BY 2 FOR THE SPECIAL CARDS
            }
            else {
                addCard(colors[i], number, 2); // Add two cards of the same color and number
            }
        }
    }
    // DEBUG PRINT
    //std::cout << "Total number of cards: " << totalCards << std::endl;
}

// Helper function to add cards with the same color and number
void Deck::addCard(const std::string& color, int number, int count) {
    for (int i = 0; i < count; i++) {
        cards.emplace_back(color, number);
    }
}

// Helper function to add special cards for a color
void Deck::addSpecialCards(const std::string& color) {
    addCard(color, -1, 2); // Add two Reverse cards
    addCard(color, -2, 2); // Add two Plus2 cards
    addCard(color, -3, 2); // Add two Skip cards
    addCard("wild", -4, 1); // Add one Rumble card
    addCard("wild", -5, 1); // Add one Rumble card
}

// SHUFFLE THE DECK
void Deck::shuffle() {
    // USE A RANDOM DEVICE AS A SOURCE OF RANDOMNESS
    std::random_device rd;

    // USE THE RANDOM DEVICE TO SEED THE RANDOM NUMBER GENERATOR
    std::mt19937 gen(rd());

    // SHUFFLE THE CARDS USING THE RANDOM NUMBER GENERATOR
    std::shuffle(cards.begin(), cards.end(), gen);
}

// DRAW AND REMOVE THE TOP CARD FROM THE DECK
Card Deck::drawCard() {
    if (!cards.empty()) {
        Card topCard = cards.back();
        cards.pop_back();
        return topCard;
    }
    else {
        // HANDLE THE CASE WHEN THE DECK IS EMPTY
        return Card("EMPTY", -1); // YOU CAN CREATE A SPECIAL "EMPTY" CARD
    }
}

// DISPLAY THE ENTIRE DECK ON THE WINDOW
void Deck::displayDeck(sf::RenderWindow& window) {
    const float cardWidth = cards[0].getTexture().getSize().x;
    const float cardHeight = cards[0].getTexture().getSize().y;
    float yOffset = 7.0;
    float leftXOffset = 20.0;
    const float cardSpacing = 10.0f;
    for (Card& card : cards) {
        sf::Sprite cardSprite;
        cardSprite.setTexture(card.getTexture());
        cardSprite.setPosition(leftXOffset, yOffset);
        cardSprite.setScale(0.2f, 0.2f);
        window.draw(cardSprite);
        leftXOffset += cardSpacing;
    }
}





