#include "Text.h"
#include <iostream>

// Default constructor
Text::Text() {}

// Parameterized constructor
Text::Text(float size, sf::Color textColor, sf::Font& font, std::string string, sf::Vector2f pos) {
    sfText.setFont(font);
    sfText.setCharacterSize(size * 10);
    sfText.setScale(0.1f, 0.1f);
    sfText.setFillColor(textColor);
    sfText.setString(string);

    xPos = pos.x;
    yPos = pos.y;
    sfText.setPosition(pos);
}

// Set the origin of the text
void Text::SetOrigin() {
    sfText.setOrigin(sf::Vector2f(sfText.getLocalBounds().width / 2, sfText.getLocalBounds().height / 2));
}

// Set the position of the text with scaling factors
void Text::SetPositionWithFactor(sf::RenderWindow& window, float xFactor, float yFactor) {
    sfText.setPosition(window.mapPixelToCoords(sf::Vector2i(xPos * xFactor, yPos * yFactor)));
}

// Draw the text on the window
void Text::Draw(sf::RenderWindow& window) {
    window.draw(sfText);
}

// Set the position of the text
void Text::SetPosition(sf::Vector2f pos) {
    xPos = pos.x;
    yPos = pos.y;

    sfText.setPosition(pos);
}

// Set the string of the text
void Text::SetString(std::string string) {
    sfText.setString(string);
}

// Destructor
Text::~Text() {}
