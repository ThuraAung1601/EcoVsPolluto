// Button.cpp
#include "Button.h"

// Default constructor.
Button::Button() {}

// Constructor to initialize the button.
Button::Button(int buttonId, sf::Texture* texture, sf::Texture* activeTexture, sf::Vector2f pos, sf::Font& font, float textSize, bool setOrigin, std::string text, bool updateSprite) {
    // Set smooth property for textures.
    texture->setSmooth(true);
    activeTexture->setSmooth(true);

    // Set up button properties.
    body.setTexture(texture);
    body.setPosition(pos);
    body.setSize(sf::Vector2f(texture->getSize().x, texture->getSize().y));

    buttonText = Text(textSize, sf::Color::Black, font, text, sf::Vector2f(0.0f, 0.0f));

    if (setOrigin) {
        body.setOrigin(sf::Vector2f(texture->getSize().x / 2, texture->getSize().y / 2));
        buttonText.SetOrigin();
    }

    this->updateSprite = updateSprite;
    activeButton = activeTexture;
    buttonTexture = texture;
    xPos = pos.x;
    this->buttonId = buttonId;
    yPos = pos.y;
}

// Set the texture of the button.
void Button::SetTexture(sf::Texture* texture, bool setOrigin) {
    buttonTexture = texture;
    body.setSize(sf::Vector2f(texture->getSize().x, texture->getSize().y));

    if (setOrigin) {
        body.setOrigin(sf::Vector2f(texture->getSize().x / 2, texture->getSize().y / 2));
    }

    body.setTexture(buttonTexture);
}

// Set the scale of the button.
void Button::SetScale(sf::Vector2f scale) {
    body.setScale(scale);
}

// Set the size of the button.
void Button::SetSize(sf::Vector2f size) {
    body.setSize(size);
}

// Set the text displayed on the button.
void Button::SetButtonText(std::string string) {
    buttonText.SetString(string);
}

// Change the texture of the button.
void Button::ChangeButtonTexture(sf::Texture* texture) {
    body.setTexture(texture);
}

// Set the position and texture of the button.
void Button::SetButton(sf::Texture* texture, sf::Vector2f pos, std::string text) {
    body.setTexture(texture);
    body.setPosition(pos);
}

// Draw the button on the given render window.
void Button::Draw(sf::RenderWindow& window) {
    window.draw(body);
    buttonText.Draw(window);
}

// Set the position of the button relative to the window size.
void Button::SetPositionWithFactor(sf::RenderWindow& window, float xFactor, float yFactor) {
    body.setPosition(window.mapPixelToCoords(sf::Vector2i(xPos * xFactor, yPos * yFactor)));
    buttonText.SetPosition(window.mapPixelToCoords(sf::Vector2i(xPos * xFactor, yPos * yFactor)));
}

// Check if the mouse is hovering over the button.
bool Button::mouseHover(sf::Vector2f mousePos) {
    if (body.getGlobalBounds().contains(mousePos)) {
        if (updateSprite) {
            body.setTexture(activeButton);
        }
        return true;
    }

    if (updateSprite) {
        body.setTexture(buttonTexture);
    }

    return false;
}

// Change the button's texture when selected.
void Button::Selected(bool selected) {
    if (updateSprite) {
        if (selected) {
            body.setTexture(activeButton);
        } else {
            body.setTexture(buttonTexture);
        }
    }
}

// Destructor.
Button::~Button() {}