# EcoVsPolluto

EcoVsPolluto is a platform-based 2-dimensional game. The gaming logic and physics are based on Super Mario.
The graphics were renovated by our team. We included the map editing feature. The game is separated into four levels.

## Team
1. Thura Aung <66011606@kmitl.ac.th>
2. Eaint Kay Khaing Kyaw
3. Yanin Saema

## Code analysis 
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



## References
1. Suraj Sharma, C++ SFML Simple Apps and Games, Youtube, Link: https://youtube.com/playlist?list=PL6xSOsbVA1eb_QqMTTcql_3PdOiE928up&si=ZOFt8-5293jz-gCa
2. Hello World Guy, Advanced Mario Game C++/SFML, Youtube, Link: https://youtu.be/aCq7P0e4cv0?si=2r6HnZkbE0ka5GQH
