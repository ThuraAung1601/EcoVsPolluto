// GUIManager.h

#pragma once

#include "Panel.h"
#include <iostream>
#include "LevelManager.h"

// Class responsible for managing the graphical user interface of the game
class GUIManager
{
public:
	// Constructor
	GUIManager(sf::RenderWindow& window, sf::Vector2f windowSize);

	// Destructor
	~GUIManager();

	// Enum representing different types of panels
	enum PanelType { 
	   Menu, 
	   Levels, 
	   GameOver, 
	   GameOverlay, 
	   LevelFinished, 
	   Editor, 
	   Pause, 
	   Credits, 
	   Controls 
	 };
	// The current active panel type
	PanelType panel = Menu;

	// Handles the active panel based on user interactions
	void HandlePanel(sf::RenderWindow& window, sf::Vector2f size);

	// Updates the active panel
	void UpdatePanel(sf::RenderWindow& window, bool levelEditorEnabled);

	// Updates the UI for the level editor
	void EditorUI(int currentTile);

	// Updates the text of a specific UI element
	void UpdateText(int textIndex, std::string newText);

	// Sets the active panel
	void SetPanel(PanelType currentPanelType, sf::Vector2f scaleFactor, sf::Vector2f windowSize);

	// Handles button click events
	void ClickButton();

	// Retrieves the selected level
	int GetSelectedLevel();

	// Checks if the specified panel type is currently active
	bool CheckIfCurrentWindow(PanelType panel);

	// Retrieves the ID of the currently pressed button
	int GetCurrentButtonId();

	// ID of the currently pressed button
	int currentButton = -1;

	// Pointer to the current active panel
	Panel* currentPanel;

	// Flag indicating whether the game is currently in the menu
	bool inMenu = true;

private:
	LevelManager levelManager; // Instance of LevelManager for managing game levels
	sf::Texture buttonTexture; // Texture for buttons
	sf::Texture coinTexture; // Texture for coins
	sf::Texture buttonActiveTexture; // Texture for active buttons
	sf::Texture buttonSmallTexture; // Texture for small buttons
	sf::Texture buttonSmallActiveTexture; // Texture for active small buttons
	sf::Font font; // Font for text rendering
};
