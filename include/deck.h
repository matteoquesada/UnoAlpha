#pragma once 
#include <SFML/Graphics.hpp>
#include "card.h" // Include your Card class header

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

    void addCard(const std::string& color, int number, int count);
    void addSpecialCards(const std::string& color);
    std::vector<Card> cards; // A vector to store the cards in the deck
};


