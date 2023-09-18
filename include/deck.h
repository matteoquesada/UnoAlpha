#ifndef DECK_H
#define DECK_H

#include <SFML/Graphics.hpp>
#include "card.h" // Include your Card class header

class Deck {
public:
    Deck();

    void shuffle();

    Card drawCard();

    void displayDeck(sf::RenderWindow& window);

private:
    std::vector<Card> cards;
};

#endif
