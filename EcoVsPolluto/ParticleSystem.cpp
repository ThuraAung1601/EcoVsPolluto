#include "ParticleSystem.h"
#include <iostream>
#include <stdlib.h>

// Constructor
ParticleSystem::ParticleSystem() {}

ParticleSystem::ParticleSystem(int particlesCount, sf::Texture& particleTexture, sf::Vector2f spawnPos, float spawnSpeed, float lifeTime, sf::Vector2i minVelocity, sf::Vector2i maxVelocity) {
    this->spawnSpeed = spawnSpeed;
    this->particlesCount = particlesCount;
    this->particleTexture = particleTexture;
    this->lifeTime = lifeTime;
    timer = spawnSpeed;
    this->minVelocity = minVelocity;
    this->maxVelocity = maxVelocity;
    this->startSize = startSize;
}

// Update particles function
void ParticleSystem::UpdateParticles(float deltaTime, sf::Vector2f spawnPos, float dir, float burst) {
    if (timer <= 0.0f) {
        timer = spawnSpeed;
        for (int i = 0; i < burst; i++) {
            if (particlesCount > currentParticles) {
                particles.push_back(new Particle(spawnPos, sf::Vector2f((rand() % maxVelocity.x + minVelocity.x) * dir, (rand() % maxVelocity.y + minVelocity.y)), particleTexture, lifeTime));
                currentParticles++;
            }
        }
    }
    timer -= deltaTime;
    for (int i = 0; i < particles.size(); i++) {
        if (i < particles.size()) {
            if (particles[i]->lifeTime < 0) {
                oldParticles.push_back(particles[i]);
                delete particles[i];
                particles[i] = NULL;
                particles.erase(particles.begin() + i);
                currentParticles--;
            }
            else {
                particles[i]->pos += particles[i]->vel * deltaTime;
                particles[i]->sprite.setPosition(particles[i]->pos);
                particles[i]->lifeTime -= deltaTime;
                float scale = particles[i]->lifeTime / lifeTime;
                if (scale < 0) {
                    scale = 0;
                }
                particles[i]->sprite.setScale(scale, scale);
            }
        }
    }
}

// Draw function
void ParticleSystem::Draw(sf::RenderWindow& window) {
    for (int i = 0; i < particles.size(); i++) {
        window.draw(particles[i]->sprite);
    }
}

// Destructor
ParticleSystem::~ParticleSystem() {}