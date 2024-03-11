#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Text.h"

// Class representing a panel containing buttons and text
class Panel
{
public:
    // Default constructor
    Panel();

    // Constructor with background color
    Panel(sf::Vector2f size, sf::Color backgroundColor, sf::Vector2f pos);

    // Constructor with background texture
    Panel(sf::Vector2f size, sf::Texture& backgroundTexture, sf::Vector2f pos);

    // Destructor
    ~Panel();

    // Handle the panel, including drawing buttons and text
    void HandlePanel(sf::RenderWindow& window, sf::Vector2f size);

    // Update the panel based on mouse position and selected button
    void UpdatePanel(sf::RenderWindow& window, int selectedButton);

    // Vector of buttons contained within the panel
    std::vector<Button*> buttons;

    // Vector of text objects contained within the panel
    std::vector<Text*> texts;

    // ID of the currently selected button
    int currentButtonId = 0;

    // Index of the currently selected button in the buttons vector
    int currentButtonIndex = 0;

private:
    // Rectangle shape representing the panel body
    sf::RectangleShape body;

    // Size of the panel before any scaling
    sf::Vector2f oldSize;
};