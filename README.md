# EcoVsPolluto

Github Link: https://github.com/ThuraAung1601/EcoVsPolluto

EcoVsPolluto is a platform-based 2-dimensional game. The gaming logic and physics are based on Super Mario.
The graphics were renovated by our team. We included the map editing feature. The game is separated into four levels.

## Team
1. Thura Aung <66011606@kmitl.ac.th>
2. Eaint Kay Khaing Kyaw <66011533@kmitl.ac.th>
3. Yanin Saema <66011301@kmitl.ac.th>

## Code Overview Analysis 
### Classes
1. Animation: for handling sprite animations.
2. Button: for creating interactive buttons in a graphical user interface.
3. Collider: for handling collision detection and response.
4. GUIManager: for managing the graphical user interface of the game
5. GameManager: for managing the game loop, user input, and game state.
6. LevelManager: for managing the level
7. Panel: for creating panel object to contain Buttons and Texts
8. Particle: for creating particles (leaf and trail) 
9. ParticleSystem: for movement of the Particle objects
10. Player: for creating Player object and movements
11. SoundManager: for the sound tracks
12. Text: for rendering to display the SFML text object
13. Tile: for creating Tile object

### Polymorphism and Inheritance
Tile class is an abstract class with derived classes - Coin and Enemy.

### Pointer
this-> pointer is used to explicitly refer to the current object instance within a member function of that object. It is used for clarity to avoid confusion and ensures to access the intended member variable of the object.
```
// GUIManager.h
// used for clarity
		this->currentPanel = new Panel(windowSize, sf::Color::Transparent, sf::Vector2f(0.0f, 0.0f));
```

unique_ptr is used for direct manipulation of Tile objects (Coin and Enemy).
```
std::unique_ptr<Coin>(new Coin(levelTextures[tileId], sf::Vector2f(35.0f, 50.0f), pos, tileId, sf::Vector2f(17.5f, 25.0f)))
```

### Pass by Reference
& symbol is used in function parameters to denote that the arguments being passed are references rather than values.

```
// GameManager.cpp
GameManager::GameManager(sf::RenderWindow& window, sf::Texture& backgroundTexture, LevelManager& levelManager, GUIManager& guiManager, sf::Sprite& background, int currentLevel, sf::Vector2f& originalSize, SoundManager& soundManager) {
    // Assign sound manager
    this->soundManager = &soundManager;
```

### enum
enum is a user-defined type. We used to assign Panel Objects.
```
// GUIManager.h
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
```

### struct
struct is a user-defined data type that allows grouping multiple variables of different types under a single name together. For example, we used struct to save Tile informations - id and position.

```
// LevelManager.h
struct TileId {
	int tileId;
	sf::Vector2f position;
};
```

## Media 
### Graphic 
Bayat: https://bayat.itch.io/platform-game-assets

### Sound track
Zapsplat: https://www.zapsplat.com

## References
1. Suraj Sharma, C++ SFML Simple Apps and Games, Youtube, Link: https://youtube.com/playlist?list=PL6xSOsbVA1eb_QqMTTcql_3PdOiE928up&si=ZOFt8-5293jz-gCa
2. Hello World Guy, Advanced Mario Game C++/SFML, Youtube, Link: https://youtu.be/aCq7P0e4cv0?si=2r6HnZkbE0ka5GQH
