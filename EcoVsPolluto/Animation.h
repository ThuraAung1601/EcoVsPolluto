// Animation.h
#pragma once

#include <SFML/Graphics.hpp>

// Animation class for handling sprite animations.
class Animation {
	public:
		sf::IntRect uvRect; // Rectangle defining the portion of the texture to display for the current frame.
		int currentImage; // Index of the current frame.
		bool loop = true; // Flag indicating whether the animation should loop.

		// Constructor for creating an animation object.
		// Parameters:
		//   texture: Reference to the texture used for animation frames.
		//   firstFrame: Index of the first frame in the texture.
		//   lastFrame: Index of the last frame in the texture.
		//   imageCount: Total number of frames in the animation.
		//   switchTime: Time (in seconds) between frame switches.
		Animation(sf::Texture& texture, int firstFrame, int lastFrame, int imageCount, float switchTime);

		// Destructor for cleaning up resources.
		~Animation();

		// Update function to advance the animation.
		// Parameters:
		//   startFrame: Index of the starting frame of the animation sequence.
		//   lastFrame: Index of the last frame of the animation sequence.
		//   deltaTime: Time (in seconds) elapsed since the last frame.
		//   flip: Flag indicating whether the animation sprite should be flipped.
		void Update(int startFrame, int lastFrame, float deltaTime, bool flip);

	private:
		int imageCount; // Total number of frames in the animation.
		double totalTime; // Total time elapsed since the animation started.
		double switchTime; // Time (in seconds) between frame switches.
};