// Collider.h
#pragma once
#include <SFML/Graphics.hpp>

// Collider class for handling collision detection and response.
class Collider {
	public:
		// Constructor.
		Collider(sf::RectangleShape& body);

		// Destructor.
		~Collider();

		// Move the collider by a specified amount.
		void Move(float dx, float dy) {
			body.move(dx, dy);
		}

		// Check for collision with another collider.
		bool checkCollision(Collider other, sf::Vector2f& direction, float push, float offsetX, float offsetY, sf::Vector2f posOffset, sf::Vector2f intersect);

		// Get the position of the collider.
		sf::Vector2f GetPosition() {
			return body.getPosition();
		}

		// Get the half-size of the collider.
		sf::Vector2f GetHalfSize() {
			return body.getSize() / 2.0f;
		}

	private:
		sf::RectangleShape& body; // Reference to the shape of the collider.
};