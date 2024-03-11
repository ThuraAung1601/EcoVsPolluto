#include "Particle.h"

// Constructor for Particle class
Particle::Particle(sf::Vector2f pos, sf::Vector2f vel, sf::Texture& texture, float lifeTime) {
    // Initialize position, velocity, sprite, texture, and lifetime
    this->pos = pos;
    this->vel = vel;
    this->sprite = sf::Sprite();
    this->texture = texture;
    this->lifeTime = lifeTime;

    // Set texture properties
    texture.setSmooth(true);

    // Set sprite properties
    sprite.setPosition(pos);
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}

// Destructor for Particle class
Particle::~Particle() { }