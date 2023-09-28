#pragma once
#include <SFML/Graphics.hpp> // INCLUDE THE SFML LIBRARY FOR GRAPHICS

class Card {
public:
    // CONSTRUCTOR TO INITIALIZE A CARD WITH A GIVEN COLOR AND NUMBER
    Card(const std::string& color, int number);

    // FUNCTION TO SET THE CARD'S TEXTURE BASED ON ITS COLOR AND NUMBER
    void setCardTexture();

    // FUNCTION TO GET THE CARD'S TEXTURE
    sf::Texture& getTexture();

    // FUNCTION TO GET THE CARD'S NUMBER
    int getNumber() const;

    // FUNCTION TO SET MANUALLY THE CARD'S COLOR
    void setColor(const std::string& color);

    // FUNCTION TO GET THE CARD'S COLOR
    std::string getColor() const;

    // FUNCTION TO GET THE CARD'S TYPE
    std::string getType() const;

    // COPY ASSIGNMENT OPERATOR
    Card& operator=(const Card& other);

    // FUNCTION TO GET THE CARD'S SIZE
    sf::Vector2u getSize() const;

    // FUNCTION TO GET THE BACK TEXTURE OF THE CARD
    sf::Texture& getBackTexture();

    // FUNCTION TO PERFORM A CARD ACTION
    void action();

    // FUNCTION TO CHECK IF THE CARD IS SPECIAL
    bool isSpecial();

    // FUNCTION TO CHECK IF THE CARD IS WILD
    bool isWild();

private:
    sf::Texture texture; // TEXTURE FOR THE CARD
    std::string type;    // TYPE OF THE CARD (SPECIAL OR REGULAR)
    std::string color;   // COLOR OF THE CARD
    sf::Sprite sprite;   // SPRITE FOR THE CARD
    sf::Texture backTexture; // BACK TEXTURE FOR THE CARD
    int number;          // NUMBER OF THE CARD
};
