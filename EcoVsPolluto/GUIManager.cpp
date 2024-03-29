#include "GUIManager.h"
#include <iostream>

// GUIManager constructor
GUIManager::GUIManager(sf::RenderWindow& window, sf::Vector2f windowSize) {
	buttonTexture.loadFromFile("Textures/buttonActive.png");
	coinTexture.loadFromFile("Textures/transparent_coin.png");
	buttonActiveTexture.loadFromFile("Textures/button.png");
	buttonSmallTexture.loadFromFile("Textures/buttonActiveSmall.png");
	buttonSmallActiveTexture.loadFromFile("Textures/buttonSmall.png");
	font.loadFromFile("Font/RifficFree-Bold.ttf");
	SetPanel(Menu,sf::Vector2f(1.0f,1.0f), windowSize);
}

// Makes a panel with the needed text fields and buttons
void GUIManager::SetPanel(PanelType currentPanelType, sf::Vector2f scaleFactor, sf::Vector2f windowSize) {
	panel = currentPanelType;
	currentButton = 0;
	switch (currentPanelType) {
	// Menu State
	case Menu:
		inMenu = true;
		this->currentPanel = new Panel(windowSize, sf::Color::Transparent, sf::Vector2f(0.0f, 0.0f));
		this->currentPanel->texts.push_back(new Text(30, sf::Color::Black, font, "Menu", sf::Vector2f(256.0f*scaleFactor.x, 50.0f*scaleFactor.y)));
		this->currentPanel->texts[0]->SetOrigin();
		this->currentPanel->buttons.push_back(new Button(1, &buttonTexture, &buttonActiveTexture, sf::Vector2f(256.0f*scaleFactor.x, 150.0f*scaleFactor.y), font, 20.0f, true, "Start"));
		this->currentPanel->buttons.push_back(new Button(7, &buttonTexture, &buttonActiveTexture, sf::Vector2f(256.0f*scaleFactor.x, 250.0f*scaleFactor.y), font, 20.0f, true, "Levels"));
		this->currentPanel->buttons.push_back(new Button(13, &buttonTexture, &buttonActiveTexture, sf::Vector2f(256.0f*scaleFactor.x, 350.0f*scaleFactor.y), font, 20.0f, true, "Controls"));
		this->currentPanel->buttons.push_back(new Button(2, &buttonTexture, &buttonActiveTexture, sf::Vector2f(256.0f*scaleFactor.x, 450.0f*scaleFactor.y), font, 20.0f, true, "Exit"));
		this->currentPanel->buttons.push_back(new Button(9, &buttonSmallTexture, &buttonSmallActiveTexture, sf::Vector2f(52.0f*scaleFactor.x, 480.0f*scaleFactor.y), font, 12.0f, true, "About"));
		this->currentPanel->buttons.push_back(new Button(14, &buttonSmallTexture, &buttonSmallActiveTexture, sf::Vector2f(460.0f*scaleFactor.x, 480.0f*scaleFactor.y), font, 12.0f, true, "Toggle Fullscreen"));
		this->currentPanel->buttons.push_back(new Button(15, &buttonSmallTexture, &buttonSmallActiveTexture, sf::Vector2f(460.0f*scaleFactor.x, 430.0f*scaleFactor.y), font, 12.0f, true, "Sounds Off!"));
		break;

	// Level picking State
	case Levels:
		inMenu = true;
		this->currentPanel = new Panel(windowSize, sf::Color::Transparent, sf::Vector2f(0.0f, 0.0f));
		this->currentPanel->texts.push_back(new Text(30, sf::Color::Black, font, "Level Select", sf::Vector2f(246.0f*scaleFactor.x, 50.0f*scaleFactor.y)));
		this->currentPanel->texts[0]->SetOrigin();
		this->currentPanel->buttons.push_back(new Button(6, &buttonTexture, &buttonActiveTexture, sf::Vector2f(256.0f*scaleFactor.x, 150.0f*scaleFactor.y), font, 20.0f, true, "Level 1"));
		this->currentPanel->buttons.push_back(new Button(6, &buttonTexture, &buttonActiveTexture, sf::Vector2f(256.0f*scaleFactor.x, 225.0f*scaleFactor.y), font, 20.0f, true, "Level 2"));
		this->currentPanel->buttons.push_back(new Button(6, &buttonTexture, &buttonActiveTexture, sf::Vector2f(256.0f*scaleFactor.x, 300.0f*scaleFactor.y), font, 20.0f, true, "level 3"));
		this->currentPanel->buttons.push_back(new Button(6, &buttonTexture, &buttonActiveTexture, sf::Vector2f(256.0f*scaleFactor.x, 375.0f*scaleFactor.y), font, 20.0f, true, "Level 4"));
		this->currentPanel->buttons.push_back(new Button(5, &buttonTexture, &buttonActiveTexture, sf::Vector2f(256.0f*scaleFactor.x, 450.0f*scaleFactor.y), font, 20.0f, true, "Menu"));
		break;

	// GameOver State
	case GameOver:
		inMenu = true;
		this->currentPanel = new Panel(windowSize, sf::Color::Transparent, sf::Vector2f(0.0f, 0.0f));
		this->currentPanel->texts.push_back(new Text(30, sf::Color::Black, font, "GameOver!", sf::Vector2f(246.0f*scaleFactor.x, 50.0f*scaleFactor.y)));
		this->currentPanel->texts[0]->SetOrigin();
		this->currentPanel->buttons.push_back(new Button(4, &buttonTexture, &buttonActiveTexture, sf::Vector2f(256.0f*scaleFactor.x, 190.0f*scaleFactor.y), font, 20.0f, true, "Restart"));
		this->currentPanel->buttons.push_back(new Button(5, &buttonTexture, &buttonActiveTexture, sf::Vector2f(256.0f*scaleFactor.x, 280.0f*scaleFactor.y), font, 20.0f, true, "Menu"));
		break;

	// Game Overlay
	case GameOverlay:
		inMenu = false;
		this->currentPanel = new Panel(windowSize, sf::Color::Transparent, sf::Vector2f(0.0f, 0.0f));
		this->currentPanel->texts.push_back(new Text(20, sf::Color::Black, font, "Time: 0", sf::Vector2f(10.0f*scaleFactor.x, 10.0f*scaleFactor.y)));
		this->currentPanel->texts.push_back(new Text(20, sf::Color::Black, font, "HighScore: 0", sf::Vector2f(10.0f*scaleFactor.x, 50.0f*scaleFactor.y)));
		this->currentPanel->texts.push_back(new Text(20, sf::Color::Black, font, "Plants: 0", sf::Vector2f(10.0f*scaleFactor.x, 30.0f*scaleFactor.y)));
		break;

	// Level finished State
	case LevelFinished:
		inMenu = true;
		this->currentPanel = new Panel(windowSize, sf::Color::Transparent, sf::Vector2f(0.0f, 0.0f));
		this->currentPanel->texts.push_back(new Text(20, sf::Color::Black, font, "Time: 00", sf::Vector2f(246.0f*scaleFactor.x, 100.0f*scaleFactor.y)));
		this->currentPanel->texts.push_back(new Text(20, sf::Color::Black, font, "HighScore: 00", sf::Vector2f(246.0f*scaleFactor.x, 160.0f*scaleFactor.y)));
		this->currentPanel->texts.push_back(new Text(20, sf::Color::Black, font, "Plants: 00", sf::Vector2f(246.0f*scaleFactor.x, 130.0f*scaleFactor.y)));
		this->currentPanel->texts.push_back(new Text(20, sf::Color::Black, font, "Score: 00", sf::Vector2f(246.0f*scaleFactor.x, 190.0f*scaleFactor.y)));
		this->currentPanel->texts.push_back(new Text(30, sf::Color::Black, font, "Finished!", sf::Vector2f(246.0f*scaleFactor.x, 50.0f*scaleFactor.y)));
		this->currentPanel->texts[0]->SetOrigin();
		this->currentPanel->texts[1]->SetOrigin();
		this->currentPanel->texts[2]->SetOrigin();
		this->currentPanel->texts[3]->SetOrigin();
		this->currentPanel->texts[4]->SetOrigin();
		this->currentPanel->buttons.push_back(new Button(3, &buttonTexture, &buttonActiveTexture, sf::Vector2f(256.0f*scaleFactor.x, 250.0f*scaleFactor.y), font, 20.0f, true, "Next Level!"));
		this->currentPanel->buttons.push_back(new Button(4, &buttonTexture, &buttonActiveTexture, sf::Vector2f(256.0f*scaleFactor.x, 350.0f*scaleFactor.y), font, 20.0f, true, "Restart"));
		this->currentPanel->buttons.push_back(new Button(5, &buttonTexture, &buttonActiveTexture, sf::Vector2f(256.0f*scaleFactor.x, 450.0f*scaleFactor.y), font, 20.0f, true, "Menu"));
		break;

	// Map Editor State
	case Editor:
		inMenu = false;
		this->currentPanel = new Panel(windowSize, sf::Color::Transparent, sf::Vector2f(0.0f, 0.0f));
		this->currentPanel->texts.push_back(new Text(20, sf::Color::Black, font, "Edit Mode!", sf::Vector2f(246.0f*scaleFactor.x, 50.0f)));
		this->currentPanel->texts[0]->SetOrigin();
		this->currentPanel->buttons.push_back(new Button(0, &levelManager.levelTextures[0], &buttonActiveTexture, sf::Vector2f(20.0f*scaleFactor.x, 10.0f*scaleFactor.y), font, 20.0f, false, "<1  2>", false));
		this->currentPanel->buttons.push_back(new Button(0, &levelManager.eraser, &buttonActiveTexture, sf::Vector2f(100.0f*scaleFactor.x, 10.0f*scaleFactor.y), font, 20.0f, false, "3", false));
		break;

	// Pause Menu State
	case Pause:
		inMenu = true;
		this->currentPanel = new Panel(windowSize, sf::Color::Transparent, sf::Vector2f(0.0f, 0.0f));
		this->currentPanel->texts.push_back(new Text(30, sf::Color::Black, font, "Pause", sf::Vector2f(246.0f*scaleFactor.x, 50.0f*scaleFactor.y)));
		this->currentPanel->texts[0]->SetOrigin();
		this->currentPanel->buttons.push_back(new Button(8, &buttonTexture, &buttonActiveTexture, sf::Vector2f(256.0f*scaleFactor.x, 190.0f*scaleFactor.y), font, 20.0f, true, "Continue"));
		this->currentPanel->buttons.push_back(new Button(5, &buttonTexture, &buttonActiveTexture, sf::Vector2f(256.0f*scaleFactor.x, 280.0f*scaleFactor.y), font, 20.0f, true, "Menu"));
		break;
	
	// Credits page
	case Credits:
		inMenu = true;
		this->currentPanel = new Panel(windowSize, sf::Color::Transparent, sf::Vector2f(0.0f, 0.0f));
		this->currentPanel->texts.push_back(new Text(30, sf::Color::Black, font, "About", sf::Vector2f(256.0f*scaleFactor.x, 50.0f*scaleFactor.y)));
		this->currentPanel->texts[0]->SetOrigin();
		this->currentPanel->texts.push_back(new Text(20, sf::Color::Black, font, "Thura, Eaint, Yanin", sf::Vector2f(312.0f*scaleFactor.x, 170.0f*scaleFactor.y)));
		this->currentPanel->texts.push_back(new Text(20, sf::Color::Black, font, "Used the art from: Bayat", sf::Vector2f(312.0f*scaleFactor.x, 220.0f*scaleFactor.y)));
		this->currentPanel->texts.push_back(new Text(20, sf::Color::Black, font, "Used a tutorial to begin \nwith from: Hilze Vonck", sf::Vector2f(312.0f*scaleFactor.x, 270.0f*scaleFactor.y)));
		this->currentPanel->texts.push_back(new Text(20, sf::Color::Black, font, "Sounds are from Zapsplat", sf::Vector2f(312.0f*scaleFactor.x, 320.0f*scaleFactor.y)));
		this->currentPanel->texts[1]->SetOrigin();
		this->currentPanel->texts[2]->SetOrigin();
		this->currentPanel->texts[3]->SetOrigin();
		this->currentPanel->texts[4]->SetOrigin();
		this->currentPanel->buttons.push_back(new Button(11, &buttonTexture, &buttonActiveTexture, sf::Vector2f(100.0f*scaleFactor.x, 228.0f*scaleFactor.y), font, 20.0f, true, "Link to Tutorial"));
		this->currentPanel->buttons.push_back(new Button(12, &buttonTexture, &buttonActiveTexture, sf::Vector2f(100.0f*scaleFactor.x, 128.0f*scaleFactor.y), font, 20.0f, true, "Click to Donate"));
		this->currentPanel->buttons.push_back(new Button(10, &buttonTexture, &buttonActiveTexture, sf::Vector2f(100.0f*scaleFactor.x, 300.0f*scaleFactor.y), font, 20.0f, true, "Link to Github"));
		this->currentPanel->buttons.push_back(new Button(5, &buttonTexture, &buttonActiveTexture, sf::Vector2f(100.0f*scaleFactor.x, 450.0f*scaleFactor.y), font, 20.0f, true, "Menu"));
		break;
	
	// Controls State
	case Controls:
		inMenu = true;
		this->currentPanel = new Panel(windowSize, sf::Color::Transparent, sf::Vector2f(0.0f, 0.0f));
		this->currentPanel->texts.push_back(new Text(30, sf::Color::Black, font, "Controls", sf::Vector2f(246.0f*scaleFactor.x, 50.0f*scaleFactor.y)));
		this->currentPanel->texts[0]->SetOrigin();
		this->currentPanel->texts.push_back(new Text(20, sf::Color::Black, font, "Movement:\tArrow Keys", sf::Vector2f(246.0f*scaleFactor.x, 120.0f*scaleFactor.y)));
		this->currentPanel->texts.push_back(new Text(20, sf::Color::Black, font, "Navigation:\tMouse", sf::Vector2f(246.0f*scaleFactor.x, 180.0f*scaleFactor.y)));
		this->currentPanel->texts.push_back(new Text(20, sf::Color::Black, font, "Selection:\tEnter", sf::Vector2f(246.0f*scaleFactor.x, 230.0f*scaleFactor.y)));
		this->currentPanel->texts.push_back(new Text(20, sf::Color::Black, font, "Pause:\tP", sf::Vector2f(246.0f*scaleFactor.x, 280.0f*scaleFactor.y)));
		this->currentPanel->texts.push_back(new Text(20, sf::Color::Black, font, "Escape:\tEsc", sf::Vector2f(200.0f*scaleFactor.x, 330.0f*scaleFactor.y)));
		this->currentPanel->texts.push_back(new Text(20, sf::Color::Black, font, "Edit Map:\tF10", sf::Vector2f(195.0f*scaleFactor.x, 380.0f*scaleFactor.y)));
		this->currentPanel->texts[1]->SetOrigin();
		this->currentPanel->texts[2]->SetOrigin();
		this->currentPanel->texts[3]->SetOrigin();
		this->currentPanel->texts[4]->SetOrigin();
		this->currentPanel->buttons.push_back(new Button(5, &buttonTexture, &buttonActiveTexture, sf::Vector2f(256.0f*scaleFactor.x, 450.0f*scaleFactor.y), font, 20.0f, true, "Menu"));
		break;

	default:
		break;
	}
}
void GUIManager::HandlePanel(sf::RenderWindow& window,sf::Vector2f size) {
	currentPanel->HandlePanel(window,size);
}

void GUIManager::UpdatePanel(sf::RenderWindow& window, bool levelEditorEnabled) {
	currentPanel->UpdatePanel(window,currentButton);
	
}

// The UI needed for editing a level only visible in the levels not in the menus
void GUIManager::EditorUI(int currentTile) {
	if (currentTile < 0) {
		this->currentPanel->buttons[0]->SetTexture(&levelManager.eraser, false);
		this->currentPanel->buttons[1]->SetTexture(&levelManager.levelTextures[0], false);
		this->currentPanel->buttons[0]->SetButtonText("");
		this->currentPanel->buttons[1]->SetButtonText("2");
	}
	else {
		if (currentTile != 9) {
			this->currentPanel->buttons[0]->SetTexture(&levelManager.levelTextures[currentTile], false);
		}
		else {
			this->currentPanel->buttons[0]->SetTexture(&coinTexture, false);
		}
		this->currentPanel->buttons[1]->SetTexture(&levelManager.eraser, false);
		this->currentPanel->buttons[0]->SetButtonText("<1  2>");
		this->currentPanel->buttons[1]->SetButtonText("3");
	}
	this->currentPanel->buttons[0]->SetScale(sf::Vector2f(0.5f, 0.5f));
	this->currentPanel->buttons[1]->SetScale(sf::Vector2f(0.25f, 0.25f));
}
int GUIManager::GetCurrentButtonId() {//0 when didn't click on a button
	return currentPanel->currentButtonId;
}
int GUIManager::GetSelectedLevel() {
	return currentPanel->currentButtonIndex;
} 
bool GUIManager::CheckIfCurrentWindow(PanelType panel) {
	if (this->panel == panel) {
		return true;
	}
	return false;
}
void GUIManager::UpdateText(int textIndex, std::string newText) {
	currentPanel->texts[textIndex]->SetString(newText);
}
void GUIManager::ClickButton() {

}
GUIManager::~GUIManager() { }