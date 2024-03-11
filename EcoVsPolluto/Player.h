#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animation.h"
#include "Collider.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "SoundManager.h"

class Player {
	public:
		// Constructors and Destructor
		Player(sf::Texture& texture, float switchTime, float speed, float jumpHeight, SoundManager& soundManager);
		~Player();

		// Member functions
		void Update(float deltaTime);
		void Draw(sf::RenderWindow& window);
		void SetPosition(sf::Vector2f position);
		void OnCollision(sf::Vector2f direction);
		void SetScale(sf::Vector2f scale);
		void UpdateHealthBar();
		void UpdateHealthBarPosition();

		// Public member variables
		float health = 100.0f;
		float maxHealth = 100.0f;
		bool inColdZone = false;
		bool editorMode = true;
		bool facingRight;
		bool grounded;

		// Public member functions
		sf::Vector2f GetPosition() { return body.getPosition(); }
		Collider GetCollider() { return Collider(body); }

		sf::RectangleShape body;
		Animation animation;
		float speed;
		int currentStartFrame = 0;
		int currentEndFrame = 18;
		int ffRunAnimation = 0;
		int lfRunAnimation = 17;
		int ffIdleAnimation = 18;
		int lfIdleAnimation = 29;
		int ffJumpAnimation = 30;
		int lfJumpAnimation = 31;
		sf::Vector2f velocity;
		bool canJump;
		float jumpHeight;
		sf::Sound walkSound;
		sf::SoundBuffer jumpBuffer;
		sf::Sound jumpSound;
		sf::SoundBuffer wallHitBuffer;
		sf::Sound wallHitSound;
		sf::SoundBuffer walkBuffer;
		ParticleSystem particleSystem;
		ParticleSystem trailParticleSystem;
		sf::Texture particleTexture;
		sf::Texture particleTrailTexture;
		sf::RectangleShape healthBar;
};