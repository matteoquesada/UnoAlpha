#pragma once 
#include <SFML/Graphics.hpp>
#include "card.h" // INCLUDE YOUR CARD CLASS HEADER

class Deck {
public:
    // CONSTRUCTOR TO INITIALIZE THE DECK
    Deck();
    ~Deck();

    // FUNCTION TO SHUFFLE THE DECK
    void shuffle();



    // FUNCTION TO INITIALIZE THE STASH WITH A CARD FROM THE MAIN DECK
    void initializeStash(Deck& mainDeck);

    // FUNCTION TO GET THE TOP CARD OF THE DECK
    Card getTopCard();

    // FUNCTION TO GET THE CARDS IN THE DECK
    std::vector<Card>& getCards();

    // FUNCTION TO HANDLE THE DECK, HANDLE MOUSE INTERACTIONS, AND DISPLAY CARDS
    void handleDeck(sf::RenderWindow& window, bool isControllable, int& pointerToTurn, Deck& playerHand, Deck& opponentHand, Deck& stashDeck, Deck& mainDeck);

    // FUNCTION TO DISPLAY THE ENTIRE DECK ON THE WINDOW
    void displayDeck(sf::RenderWindow& window, float xOffset, float yOffset);

    // FUNCTION TO FILL THE DECK WITH STANDARD UNO CARDS
    void fillDeck();

    // FUNCTION TO ADD A CARD TO THE DECK
    void addCard(const Card& card);

    // FUNCTION TO DRAW AND REMOVE THE TOP CARD FROM THE DECK
    Card drawCard();

    // FUNCTION TO GET THE SIZE OF THE DECK
    size_t getSize() const;

private:

    // FUNCTION TO HANDLE CARD ACTIONS WHEN PLAYED
    void cardAction(Card& card, Deck& playerHand, Deck& opponentHand, Deck& stashDeck, Deck& mainDeck, int& pointerToTurn);

    // FUNCTION TO REMOVE A CARD FROM THE DECK
    void removeCard(const Card& cardToRemove);

    // FUNCTION TO CHECK IF A CARD CAN BE PLAYED
    bool isCardPlayable(Card& playedCard, Card& targetCard);


    // FUNCTION TO CHECK IF A CARD IS CLICKED
    int isClicked(sf::RenderWindow& window);

    // FUNCTION TO GET A RANDOM COLOR
    std::string getRandomColor();

    // PRIVATE FUNCTION TO GET THE SPRITE OF A CARD
    sf::Sprite getSprite();

    // PRIVATE FUNCTION TO ADD STANDARD CARDS TO THE DECK
    void addCard(const std::string& color, int number, int count);

    // PRIVATE FUNCTION TO ADD SPECIAL CARDS TO THE DECK
    void addSpecialCards(const std::string& color);

    // VECTOR TO STORE THE CARDS IN THE DECK
    std::vector<Card> cards;

    // PRIVATE VARIABLE FOR CLICK COOLDOWN
    sf::Clock clickCooldown;
};
