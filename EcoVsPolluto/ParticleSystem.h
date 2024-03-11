#pragma once
#include <SFML/Graphics.hpp>
#include "Particle.h"

class ParticleSystem
{
public:
    // Constructors and Destructor
    ParticleSystem(int particlesCount, sf::Texture& particleTexture, sf::Vector2f spawnPos, float spawnSpeed, float lifeTime, sf::Vector2i minVelocity = sf::Vector2i(-100.0f, -100.0f), sf::Vector2i maxVelocity = sf::Vector2i(100.0f, 100.0f));
    ParticleSystem();
    ~ParticleSystem();
    
    // Member Functions
    void UpdateParticles(float deltaTime, sf::Vector2f spawnPos, float dir, float burst);
    void Draw(sf::RenderWindow& window);
    
    // Member Variables
    std::vector<Particle*> particles;
    std::vector<Particle*> oldParticles;

private:
    float spawnSpeed;
    float lifeTime;
    float timer;
    sf::Vector2i minVelocity;
    sf::Vector2i maxVelocity;
    float startSize;
    int particlesCount = 100;
    int currentParticles = 0;
    sf::Texture particleTexture;
};