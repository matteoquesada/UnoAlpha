#include <SFML/Graphics.hpp>
#include "../include/card.h" // Include your Card class header
#include "../include/deck.h" // Include your Deck class header
#include <iostream>
#include <random>
using namespace sf;

// DEFINE THE DECK CLASS TO MANAGE A COLLECTION OF CARDS
// DECK CONSTRUCTOR

Deck::Deck() {
    // Initialize the deck as empty
    //int totalCards = 0; // INITIALIZE THE TOTAL NUMBER OF CARDS TO 0 (DEBUG)

    // No need to fill the deck here; it starts empty
    // Debug print
    // std::cout << "Total number of cards: " << totalCards << std::endl;
}

// Fill the deck with cards, including special ones
void Deck::fillDeck() {
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
    // Debug print
    // std::cout << "Total number of cards: " << totalCards << std::endl;
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
        // Get the top card from the deck
        Card topCard = cards.back();
        // Remove the top card from the deck
        cards.pop_back();
        // Return the drawn card
        return topCard;
    }
    else {
        // Handle the case when the deck is empty by returning a special "EMPTY" card
        return Card("EMPTY", -1); // You can create a special "EMPTY" card
    }
}

// DISPLAY THE ENTIRE DECK ON THE WINDOW
void Deck::displayDeck(sf::RenderWindow& window) {
    const float cardWidth = cards[0].getTexture().getSize().x;
    const float cardHeight = cards[0].getTexture().getSize().y;
    float leftXOffset = 22.0;
    float yOffset = 615.0;

    const float cardSpacing = 57.0f;
    for (Card& card : cards) {
        sf::Sprite cardSprite;
        cardSprite.setTexture(card.getTexture());
        cardSprite.setPosition(leftXOffset, yOffset);
        cardSprite.setScale(1.0f, 1.0f);
        window.draw(cardSprite);
        leftXOffset += cardSpacing;
    }
}

void Deck::addCard(const Card& card) {
    cards.push_back(card);
}

size_t Deck::getSize() const {
    return cards.size();
}

const std::vector<Card>& Deck::getCards() const {
    return cards;
}






