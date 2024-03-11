// Animation.cpp
#include "Animation.h"

// Constructor for Animation class.
Animation::Animation(sf::Texture& texture, int firstFrame, int lastFrame, int imageCount, float switchTime) {
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime = 0;
    currentImage = 0;
    uvRect.width = texture.getSize().x / float(imageCount);
    uvRect.height = texture.getSize().y;
}

// Update function to handle animation frame switching.
void Animation::Update(int startFrame, int lastFrame, float deltaTime, bool flip) {
    // Accumulate time to determine when to switch frames.
    totalTime += deltaTime;
    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currentImage++;
        // Check if the animation sequence has reached its end.
        if (currentImage > lastFrame) {
            // If not looping, stay on the last frame; otherwise, loop back to the start frame.
            if (!loop) {
                currentImage = lastFrame;
            } else {
                currentImage = startFrame;
            }
        }
    }
    
    // Update the UV rectangle based on the current image and flip flag.
    if (flip) {
        uvRect.left = (currentImage + 1) * abs(uvRect.width);
        if (uvRect.left < 0) {
            uvRect.left = -uvRect.left;
        }
        uvRect.width = -abs(uvRect.width);
    } else {
        uvRect.left = currentImage * uvRect.width;
        if (uvRect.left < 0) {
            uvRect.left = -uvRect.left;
        }
        uvRect.width = abs(uvRect.width);
    }
}

// Destructor for Animation class.
Animation::~Animation() { }