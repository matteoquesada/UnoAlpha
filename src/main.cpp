#include <SFML/Graphics.hpp>
#include <iostream>
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "UNO Game");

    // Create a wallpaper, set position
    sf::Texture wallpaperTexture;
    if (!wallpaperTexture.loadFromFile("assets/wallpaper.png")) {
        printf("Handle error - failed to load wallpaper");
        // Handle the error as needed
    }
    sf::Sprite wallpaperSprite;
    wallpaperSprite.setTexture(wallpaperTexture);
    // Create a button, set position
    sf::RectangleShape button(sf::Vector2f(200, 200));
    sf::Texture buttonTexture;

    if (!buttonTexture.loadFromFile("assets/button.png")) {
        printf("Handle error - failed to load texture");
        // You can print an error message or take appropriate action here
    }
    button.setTexture(&buttonTexture);
    button.setPosition(500, 400);

    sf::Texture logoTexture;
    if (!logoTexture.loadFromFile("assets/unoTitle.png")) {
        printf("Handle error - failed to load logo");
        // Handle the error as needed
    }

    sf::Sprite logoSprite;
    logoSprite.setTexture(logoTexture);

    // Position and scale for wallpaper
    wallpaperSprite.setPosition(0, 0); // Adjust as needed

    // Position and scale for logo
    logoSprite.setPosition(50, 50); // Adjust as needed
    logoSprite.setScale(0.5f, 0.5f); // Adjust as needed

    // Main play button
    sf::Color defaultColor = sf::Color::White;
    sf::Color hoverColor = sf::Color(200, 200, 200); // Slightly darker when hovered
    sf::Color pressedColor = sf::Color(150, 150, 150); // Even darker when pressed
    sf::Color currentColor = defaultColor; // Initial color

    bool isMouseOverButton = false;
    bool isButtonPressed = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed && isMouseOverButton) {
                // Button pressed
                isButtonPressed = true;
                // You can perform any actions here when the button is pressed
                // For now, let's print "hola" to the console
                std::cout << "hola" << std::endl;
            }
            else if (event.type == sf::Event::MouseButtonReleased) {
                // Button released
                isButtonPressed = false;
            }
        }

        // Check for mouse interaction with the button
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        isMouseOverButton = button.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        // Change button color based on state
        if (isButtonPressed) {
            currentColor = pressedColor;
        }
        else if (isMouseOverButton) {
            currentColor = hoverColor;
        }
        else {
            currentColor = defaultColor;
        }

        // Update button color
        button.setFillColor(currentColor);

        window.clear();
        //draw wallpper
        window.draw(wallpaperSprite);
        // Draw the button
        window.draw(button);

        //draw logo
        window.draw(logoSprite);


        window.display();
    }

    return 0;
}
