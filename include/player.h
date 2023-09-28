#include "deck.h"

class Player {
public:
    // CONSTRUCTOR
    Player();
 
    // DRAW INITIAL CARDS FROM THE MAIN DECK
    void drawInitialHand(Deck& mainDeck, int numCards);

    // PLAY A CARD
    void playCard(Card card);

    // DRAW A CARD FROM THE MAIN DECK
    void drawCard(Deck& mainDeck);

    // GET THE PLAYER'S POINTS
    int getPoints();

    // SET THE PLAYER'S POINTS
    void setPoints(int points);

    // ADD POINTS TO THE PLAYER'S TOTAL
    void addToPoints(int points);

    // GET THE SIZE OF THE PLAYER'S HAND
    int getHandSize() const;

    // HANDLE THE PLAYER'S HAND INTERACTIONS AND DISPLAY
    void handleHand(sf::RenderWindow& window, bool isControllable, int& pointerToTurn, Deck& playerHand, Deck& opponentHand, Deck& stashDeck, Deck& mainDeck);

    // ADD A CARD TO THE PLAYER'S HAND
    void addCardToHand(Card& card);

    // GET THE PLAYER'S HAND
    Deck& getHand();

private:
    Deck hand;  // PLAYER'S HAND (DECK OF CARDS)
    int points;  // PLAYER'S POINTS
};
