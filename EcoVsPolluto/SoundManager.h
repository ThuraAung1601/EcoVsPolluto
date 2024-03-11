#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class SoundManager
{
public:
    // Set the volume for all sounds
    void SetVolume(float volume);

    // Constructor
    SoundManager();

    // Destructor
    ~SoundManager();

    // Public member variables
    float currentVolume = 100;
    std::vector<sf::Sound*> sounds;
};