#include "Panel.h"
#include <iostream>

// Default constructor
Panel::Panel() { }

Panel::Panel(sf::Vector2f size, sf::Color backgroundColor, sf::Vector2f pos)
{
    // Constructor with background color
    body.setSize(size);
    body.setFillColor(backgroundColor);
    body.setPosition(pos);
    oldSize = size;
}

Panel::Panel(sf::Vector2f size, sf::Texture& backgroundTexture, sf::Vector2f pos)
{
    // Constructor with background texture
    body.setSize(size);
    body.setTexture(&backgroundTexture);
    body.setPosition(pos);
    oldSize = size;
}

void Panel::UpdatePanel(sf::RenderWindow& window, int selectedButton)
{
    // Update panel based on mouse position and selected button
    body.setPosition(window.mapPixelToCoords(sf::Vector2i(0, 0)));
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    currentButtonId = 0;
    currentButtonIndex = -1;
    for (int i = 0; i < buttons.size(); i++) {
        if (buttons[i]->mouseHover(mousePos) || selectedButton == i) {
            if (selectedButton >= 0) {
                if (selectedButton == i) {
                    buttons[i]->Selected(true);
                }
                else {
                    buttons[i]->Selected(false);
                }
            }
            currentButtonId = buttons[i]->buttonId;
            currentButtonIndex = i;
        }
    }
}

void Panel::HandlePanel(sf::RenderWindow& window, sf::Vector2f size)
{
    // Handle panel drawing and button positioning
    body.setSize(size);
    if (body.getFillColor() != sf::Color::Transparent) {
        window.draw(body);
    }
    for (Button* b : buttons) {
        b->SetPositionWithFactor(window, size.x / oldSize.x, size.y / oldSize.y);
        b->Draw(window);
    }
    for (Text* t : texts) {
        t->SetPositionWithFactor(window, size.x / oldSize.x, size.y / oldSize.y);
        t->Draw(window);
    }
}

// Destructor Panel class
Panel::~Panel() { }