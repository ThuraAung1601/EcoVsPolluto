#include "Player.h"
#include <iostream>

Player::Player(sf::Texture& texture, float switchTime, float speed, float jumpHeight, SoundManager& soundManager) : animation(texture, 0, 17, 32, switchTime) {
    this->speed = speed;
    this->jumpHeight = jumpHeight;
    facingRight = true;
    currentStartFrame = ffIdleAnimation;
    currentEndFrame = lfIdleAnimation;
    body.setSize(sf::Vector2f(75.0f, 75.0f)); // size of player
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(220.0f, 220.0f);
    body.setTexture(&texture);
    texture.setSmooth(true);
    particleTexture.loadFromFile("Textures/leaf.png");
    particleTrailTexture.loadFromFile("Textures/resized_trail.png");
    jumpBuffer.loadFromFile("Audio/jump.wav");
    jumpSound.setBuffer(jumpBuffer);
    soundManager.sounds.push_back(&jumpSound);
    wallHitBuffer.loadFromFile("Audio/wallHit.wav");
    wallHitSound.setBuffer(wallHitBuffer);
    soundManager.sounds.push_back(&wallHitSound);
    walkBuffer.loadFromFile("Audio/steps.wav");
    walkSound.setBuffer(walkBuffer);
    walkSound.setLoop(true);
    soundManager.sounds.push_back(&walkSound);

    particleSystem = ParticleSystem(200, particleTexture, sf::Vector2f(220.0f, 220.0f), 0.3f, 1.0f, sf::Vector2i(1.0f, 1.0f), sf::Vector2i(100.0f, 100.0f));
    trailParticleSystem = ParticleSystem(500, particleTrailTexture, sf::Vector2f(220.0f, 220.0f), 0.001f, 1.0f, sf::Vector2i(-1.0f, 1.0f), sf::Vector2i(1.0f, 1.0f));
    
    // Initialize health bar
    healthBar.setSize(sf::Vector2f(100.0f, 10.0f));
    // healthBar.setFillColor(sf::Color::White);
    // Link: https://redketchup.io/color-picker
    healthBar.setFillColor(sf::Color(152, 251, 152));
    UpdateHealthBarPosition(); // Set initial position
}


Player::~Player() { }

// Set the position of the player
void Player::SetPosition(sf::Vector2f position) {
    body.setPosition(position);
    UpdateHealthBarPosition(); 
}

// Move the player's health
void Player::SetScale(sf::Vector2f scale) {
    UpdateHealthBarPosition();
}

// Update player logic
void Player::Update(float deltaTime) {
    velocity.x *= 0.5f;
    if (editorMode) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            velocity.x -= speed;
            facingRight = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            velocity.x += speed;
            facingRight = true;
        }
        SetScale(sf::Vector2f(health / maxHealth, health / maxHealth));
    }
    else {
        if (!inColdZone) {
            health -= deltaTime * 8;
        }
        SetScale(sf::Vector2f(health / maxHealth, health / maxHealth));
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            velocity.x += speed;
            facingRight = true;
        }
        else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            velocity.x -= speed;
            facingRight = false;
        }
    }

    float dir = facingRight ? 1.0f : -1.0f;

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && canJump && grounded) {
        canJump = false;
        jumpSound.play();
        if (currentStartFrame != ffJumpAnimation) {
            animation.currentImage = ffJumpAnimation;
            currentStartFrame = ffJumpAnimation;
            currentEndFrame = lfJumpAnimation;
            animation.loop = false;
        }
        velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
    }

    velocity.y += 981.0f * deltaTime;

    if (velocity.x < 4.0f && velocity.x > -4.0f) {
        if (currentStartFrame != ffIdleAnimation) {
            animation.loop = true;
            animation.currentImage = ffIdleAnimation;
            currentStartFrame = ffIdleAnimation;
            currentEndFrame = lfIdleAnimation;
        }
    }
    else {
        if (!grounded) {
            walkSound.pause();
            if (currentStartFrame != ffJumpAnimation) {
                animation.currentImage = ffJumpAnimation;
                currentStartFrame = ffJumpAnimation;
                currentEndFrame = lfJumpAnimation;
                animation.loop = false;
            }
        }
        else if (currentStartFrame != ffRunAnimation) {
            walkSound.play();
            animation.loop = true;
            animation.currentImage = ffRunAnimation;
            currentStartFrame = ffRunAnimation;
            currentEndFrame = lfRunAnimation;
        }
    }

    // Update particles
    animation.Update(currentStartFrame, currentEndFrame, deltaTime, !facingRight);
    body.setTextureRect(animation.uvRect);

    if (inColdZone) {
        particleSystem.UpdateParticles(deltaTime, body.getPosition() - sf::Vector2f(0, (health / maxHealth) * 18.5f), dir, 0);
        trailParticleSystem.UpdateParticles(deltaTime, body.getPosition() + sf::Vector2f(0, (health / maxHealth) * 18.5f), dir, 0);
    }
    else {
        particleSystem.UpdateParticles(deltaTime, body.getPosition() - sf::Vector2f(0, (health / maxHealth) * 18.5f), dir, 3);
        trailParticleSystem.UpdateParticles(deltaTime, body.getPosition() + sf::Vector2f(0, (health / maxHealth) * 18.5f), dir, 1);
    }

    body.move(velocity * deltaTime);
    // Update health bar appearance
    UpdateHealthBar();
}

// Draw the player
void Player::Draw(sf::RenderWindow& window) {
    trailParticleSystem.Draw(window);
    particleSystem.Draw(window);
    window.draw(body);
    window.draw(healthBar);
}

// Update the health bar appearance based on current health
void Player::UpdateHealthBar() {
    float healthRatio = health / maxHealth;
    healthBar.setSize(sf::Vector2f(100.0f * healthRatio, 10.0f));
}

// Update the position of the health bar relative to the player
void Player::UpdateHealthBarPosition() {
    sf::Vector2f barPosition = body.getPosition();
    barPosition.y -= body.getSize().y / 2.0f + 10.0f; // Position health bar below player body
    healthBar.setPosition(barPosition);
}

// Handle collision with environment
void Player::OnCollision(sf::Vector2f direction) {
    if (direction.x < 0.0f) {
        velocity.x = 0.0f;
        facingRight = false;
        if (!editorMode) {
            wallHitSound.play();
        }
    }
    else if (direction.x > 0.0f) {
        velocity.x = 0.0f;
        facingRight = true;
        if (!editorMode) {
            wallHitSound.play();
        }
    }
    if (direction.y < 0.0f) {
        velocity.y = 0.0f;
        canJump = true;
    }
    else if (direction.y > 0.0f) {
        velocity.y = 0.0f;
    }
}