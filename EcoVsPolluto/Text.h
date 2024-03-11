#pragma once

#include <SFML/Graphics.hpp>

class Text
{
public:
    Text(); // Default constructor
    Text(float size, sf::Color textColor, sf::Font& font, std::string string, sf::Vector2f pos); // Parameterized constructor
    ~Text(); // Destructor

    void Draw(sf::RenderWindow& window); // Draw the text on the window
    void SetPosition(sf::Vector2f pos); // Set the position of the text
    void SetPositionWithFactor(sf::RenderWindow& window, float xFactor, float yFactor); // Set the position of the text using factors
    void SetString(std::string string); // Set the string of the text
    void SetOrigin(); // Set the origin of the text

private:
    sf::Text sfText; // SFML text object
    float xPos; // X position of the text
    float yPos; // Y position of the text
};