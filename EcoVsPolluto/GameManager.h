#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "LevelManager.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include "GUIManager.h"
#include "SoundManager.h"
using namespace std;

// GameManager class responsible for managing the game loop, user input, and game state.
class GameManager {
    public:
        // Constructor to initialize GameManager object.
        GameManager(sf::RenderWindow& window, sf::Texture& backgroundTexture, LevelManager& levelManager, GUIManager& guiManager, sf::Sprite& background, int currentLevel, sf::Vector2f& originalSize, SoundManager& soundManager);

        // Destructor
        ~GameManager() {}
        
        // Process user input events.
        void CheckInput(sf::Event& event, sf::RenderWindow& window, LevelManager& levelManager, int& currentLevel, bool& levelEditorEnabled, GUIManager& guiManager, sf::Vector2f& originalSize, sf::View& view, sf::Sprite& background, int& windowWidth, float VIEW_HEIGHT);

        // Update game logic and state.
        void UpdateGame(sf::RenderWindow& window, GUIManager& guiManager, LevelManager& levelManager, float deltaTime, int currentLevel, sf::Vector2f& originalSize, sf::View& view, sf::Sprite& background, bool editorEnabled);

        // Resize the view based on the window size.
        void ResizeView(sf::RenderWindow& window, sf::View& view, float VIEW_HEIGHT);

        // Get the size of the window.
        sf::Vector2f GetWindowSize(sf::RenderWindow& window);

        Player* player; // Pointer to the player object.
        sf::Texture playerTexture; // Texture for the player.

        bool fullscreen = true; // Flag indicating whether the game is running in fullscreen mode.

    private:
        sf::Vector2f posOffset; // Offset for the player position.
        
        // Check button press events.
        void CheckButton(int currentButtonId, sf::RenderWindow& window, LevelManager& levelManager, int& currentLevel, bool& levelEditorEnabled, GUIManager& guiManager, sf::Vector2f& originalSize);

        // Reset the game state.
        void ResetGame(sf::RenderWindow& window, LevelManager& levelManager, int currentLevel);

        SoundManager* soundManager; // Pointer to the sound manager object.
        sf::SoundBuffer coinBuffer; // Sound buffer for collecting coins.
        sf::Sound coinSound; // Sound for collecting coins.
        sf::SoundBuffer dieBuffer; // Sound buffer for player death.
        sf::Sound dieSound; // Sound for player death.
        sf::SoundBuffer clickBuffer; // Sound buffer for button clicks.
        sf::Sound clickSound; // Sound for button clicks.
};