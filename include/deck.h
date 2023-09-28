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

    void addCard(const Card& card);

    size_t getSize() const;

    void cardAction(Card& card, Deck& playerHand, Deck& opponentHand, Deck& stashDeck, Deck& mainDeck, int& pointerToTurn);

    void initializeStash(Deck& mainDeck);

    void removeCard(const Card& cardToRemove);

    bool isCardPlayable(const Card& playedCard, const Card& targetCard);

    Card getTopCard();

    const std::vector<Card>& Deck::getCards() const;

    // Function to display the entire deck on the window
    //void handleDeck(sf::RenderWindow& window);

    void handleDeck(sf::RenderWindow& window, bool isControllable, int& pointerToTurn, Deck& playerHand, Deck& opponentHand, Deck& stashDeck, Deck& mainDeck);

    void displayDeck(sf::RenderWindow& window, float xOffset, float yOffset);

    void fillDeck();

    int isClicked(sf::RenderWindow& window);

    std::string getRandomColor();

private:
    sf::Clock Deck::clickCooldown;
    void addCard(const std::string& color, int number, int count);
    void addSpecialCards(const std::string& color);
    std::vector<Card> cards; // A vector to store the cards in the deck
};