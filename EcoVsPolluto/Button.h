// Button.h
#pragma once

#include <SFML/Graphics.hpp>
#include "Text.h"

// Button class for creating interactive buttons in a graphical user interface.
class Button {
	public:
		// Default constructor.
		Button();

		// Constructor to initialize the button.
		// Parameters:
		//   buttonId: Unique identifier for the button.
		//   texture: Pointer to the texture used for the button's default appearance.
		//   activeTexture: Pointer to the texture used for the button when active (e.g., when hovered over).
		//   pos: Position of the button.
		//   font: Reference to the font used for the button's text.
		//   textSize: Size of the text.
		//   setOrigin: Flag indicating whether to set the origin of the button and its text to the center.
		//   text: Text displayed on the button.
		//   updateSprite: Flag indicating whether to update the button's texture when hovered over.
		Button(int buttonId, sf::Texture* texture, sf::Texture* activeTexture, sf::Vector2f pos, sf::Font& font, float textSize, bool setOrigin, std::string text, bool updateSprite = true);

		// Destructor.
		~Button();

		// Set the texture of the button.
		void SetTexture(sf::Texture* texture, bool setOrigin);

		// Set the scale of the button.
		void SetScale(sf::Vector2f scale);

		// Set the size of the button.
		void SetSize(sf::Vector2f size);

		// Set the text displayed on the button.
		void SetButtonText(std::string string);

		// Change the texture of the button.
		void ChangeButtonTexture(sf::Texture* texture);

		// Set the position and texture of the button.
		void SetButton(sf::Texture* texture, sf::Vector2f pos, std::string text);

		// Draw the button on the given render window.
		void Draw(sf::RenderWindow& window);

		// Set the position of the button relative to the window size.
		void SetPositionWithFactor(sf::RenderWindow& window, float xFactor, float yFactor);

		// Check if the mouse is hovering over the button.
		bool mouseHover(sf::Vector2f mousePos);

		// Change the button's texture when selected.
		void Selected(bool selected);

		// Unique identifier for the button.
		int buttonId;

	private:
		sf::Texture* buttonTexture; // Pointer to the texture used for the button's default appearance.
		sf::Texture* activeButton; // Pointer to the texture used for the button when active (e.g., when hovered over).
		bool updateSprite; // Flag indicating whether to update the button's texture when hovered over.
		float xPos; // X-coordinate of the button.
		float yPos; // Y-coordinate of the button.
		sf::RectangleShape body; // Rectangle shape representing the button's visual appearance.
		Text buttonText; // Text displayed on the button.
};