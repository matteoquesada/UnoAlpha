#include <SFML/Graphics.hpp>
#include "../include/card.h" // Card class header
#include "../include/deck.h" // Deck class header
#include <iostream>
#include <random>

using namespace sf;

// CONSTRUCTOR: INITIALIZE AN EMPTY DECK
Deck::Deck() {}

// FILL THE DECK WITH STANDARD UNO CARDS
void Deck::fillDeck() {
    std::string colors[4] = { "red", "blue", "yellow", "green" };
    for (int i = 0; i < 4; i++) {
        for (int number = 0; number <= 10; ++number) {
            if (number == 0) {
                addCard(colors[i], number, 1);
            }
            else if (number == 10) {
                addSpecialCards(colors[i]);
            }
            else {
                addCard(colors[i], number, 2);
            }
        }
    }
}

// ADD STANDARD CARDS TO THE DECK
void Deck::addCard(const std::string& color, int number, int count) {
    for (int i = 0; i < count; i++) {
        cards.emplace_back(color, number);
    }
}

// ADD SPECIAL CARDS TO THE DECK
void Deck::addSpecialCards(const std::string& color) {
    addCard(color, -1, 2); // Reverse
    addCard(color, -2, 2); // Plus2
    addCard(color, -3, 2); // Skip
    addCard("wild", -4, 1); // Wild
    addCard("wild", -5, 1); // Wild Draw Four
}

// SHUFFLE THE DECK
void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(cards.begin(), cards.end(), gen);
}

// DRAW A CARD FROM THE DECK
Card Deck::drawCard() {
    if (!cards.empty()) {
        Card topCard = cards.back();
        cards.pop_back();
        return topCard;
    }
    else {
        std::cout<<"Deck is empty!"<<std::endl;
        return Card("null", -404);
    }
}

// DISPLAY DECK, HANDLE MOUSE INTERACTIONS
void Deck::handleDeck(RenderWindow& window, bool isControllable, int& pointerToTurn, Deck& playerHand, Deck& opponentHand, Deck& stashDeck, Deck& mainDeck) {
    const float cardSpacing = isControllable ? 56.0f : 29.0f;
    const float yOffset = isControllable ? 615.0f : 7.0f;
    int clickedCardIndex = -1;
    float xOffset = 22.0f;

    for (int cardIndex = 0; cardIndex < cards.size(); cardIndex++) {
        Card& card = cards[cardIndex];
        Sprite cardSprite = isControllable ? Sprite(card.getTexture()) : Sprite(card.getBackTexture());
        if (!isControllable) cardSprite.setScale(0.5f, 0.5f);
        cardSprite.setPosition(xOffset, yOffset);
        xOffset += cardSpacing;

        if (isControllable) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            if (cardSprite.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                cardSprite.setColor(Color(200, 200, 200, 255));
                if (Mouse::isButtonPressed(Mouse::Left)) clickedCardIndex = cardIndex;
            }
            else {
                cardSprite.setColor(Color(255, 255, 255, 255));
            }
        }

        window.draw(cardSprite);
    }

    if (clickedCardIndex != -1 && isControllable) {

        sf::sleep(sf::seconds(1.0f));
        cardAction(cards[clickedCardIndex], playerHand, opponentHand, stashDeck, mainDeck, pointerToTurn);
    }
}

// GET THE TOP CARD OF THE DECK
Card Deck::getTopCard() {
    return !cards.empty() ? cards.back() : Card("null", -404);
}

// CHECK IF A CARD CAN BE PLAYED
bool Deck::isCardPlayable(const Card& playedCard, const Card& targetCard) {
    std::cout<<playedCard.getColor()<<" "<<playedCard.getNumber()<<std::endl;
    std::cout<<targetCard.getColor()<<" "<<targetCard.getNumber()<<std::endl;
    return (playedCard.getColor() == targetCard.getColor() || playedCard.getNumber() == targetCard.getNumber());
}

// HANDLE CARD ACTIONS WHEN PLAYED
void Deck::cardAction(Card& card, Deck& playerHand, Deck& opponentHand, Deck& stashDeck, Deck& mainDeck, int& pointerToTurn) {
    if (isCardPlayable(card, stashDeck.getTopCard())) {
        std::cout << "Card is playable!!!!" << std::endl;
        // TO DO: SPECIAL CARDS DONT USE THE SAME NUMBER TO CHECK IF THEY ARE PLAYABLE
        // Handle regular cards
        switch (card.getNumber()) {
        case 0:
            std::swap(playerHand, opponentHand);
            break;
        case -1:
            // Reverse logic here
            break;
        case -2:
            opponentHand.addCard(mainDeck.drawCard());
            opponentHand.addCard(mainDeck.drawCard());
            pointerToTurn++;
            break;
        case -3:
            pointerToTurn += 2;
            break;
        default:
            // Check for other cards with the same number in the player's hand
            for (Card& otherCard : cards) {
                if (otherCard.getNumber() == card.getNumber() && card.getNumber() > 0) {
                    stashDeck.addCard(otherCard);
                }
            }
            pointerToTurn++;
            break;
        }

        stashDeck.addCard(card);
        playerHand.removeCard(card);
    }
    else if (card.isWild()) {
        std::cout << "Card is WILD and playable!!!!" << std::endl;

        // Change the color of the wild card
        card.setColor(getRandomColor());

        if (card.getNumber() == -4) {
            std::cout << "Wild changed color to: " << card.getColor() << std::endl;
            stashDeck.addCard(card);
            pointerToTurn++;
        }
        else if (card.getNumber() == -5) {
            std::cout << "Wild Draw Four changed color to: " << card.getColor() << std::endl;
            opponentHand.addCard(mainDeck.drawCard());
            opponentHand.addCard(mainDeck.drawCard());
            opponentHand.addCard(mainDeck.drawCard());
            opponentHand.addCard(mainDeck.drawCard());
            stashDeck.addCard(card);
            pointerToTurn++;
        }

        playerHand.removeCard(card);
    }
    else {
        std::cout << "Card is not playable!!!! (NOT WILD OR NOT SPECIAL) MEANS ERROR SO CHECK LAWS" << std::endl;
    }
}

// DISPLAY THE DECK ON THE SCREEN
void Deck::displayDeck(RenderWindow& window, float xOffset, float yOffset) {
    const float windowCenterX = 1280 / 2.0f;
    const float windowCenterY = 720 / 2.0f;
    const float cardSpacing = 2.0f; // Small spacing to see the card border

    float currentYOffset = windowCenterY - (cards.size() / 2.0f * cardSpacing);

    for (Card& card : cards) {
        Sprite cardSprite(card.getTexture());
        cardSprite.setPosition(windowCenterX - cardSprite.getGlobalBounds().width / 2,
            currentYOffset - cardSprite.getGlobalBounds().height / 2);
        window.draw(cardSprite);
        currentYOffset += cardSpacing;
    }
}

// INITIALIZE THE STASH WITH A CARD FROM THE MAIN DECK
void Deck::initializeStash(Deck& mainDeck) {
    cards.push_back(mainDeck.drawCard());
}

// ADD A CARD TO THE DECK
void Deck::addCard(const Card& card) {
    cards.push_back(card);
}

// GET THE SIZE OF THE DECK
size_t Deck::getSize() const {
    return cards.size();
}

// GET THE CARDS IN THE DECK
const std::vector<Card>& Deck::getCards() const {
    return cards;
}

// REMOVE A CARD FROM THE DECK
void Deck::removeCard(const Card& cardToRemove) {
    cards.erase(std::remove_if(cards.begin(), cards.end(),
        [&cardToRemove](const Card& card) {
            return card.getColor() == cardToRemove.getColor() &&
                card.getNumber() == cardToRemove.getNumber() &&
                card.getType() == cardToRemove.getType();
        }),
        cards.end());
}

std::string Deck::getRandomColor() {
    std::string colors[4] = { "red", "blue", "yellow", "green" };
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 3);
    return colors[dist(gen)];
}
