#include "SoundManager.h"

// Constructor
SoundManager::SoundManager() { }

// Set the volume for all sounds
void SoundManager::SetVolume(float volume) {
    currentVolume = volume;
    for (int i = 0; i < sounds.size(); i++) {
        sounds[i]->setVolume(volume);
    }
}

// Destructor
SoundManager::~SoundManager() { }