#include "GameManager.h"
#include <cstdlib>

// GameManager constructor
GameManager::GameManager(sf::RenderWindow& window, sf::Texture& backgroundTexture, LevelManager& levelManager, GUIManager& guiManager, sf::Sprite& background, int currentLevel, sf::Vector2f& originalSize, SoundManager& soundManager) {
    // Assign sound manager
    this->soundManager = &soundManager;

    // Load player texture
    playerTexture.loadFromFile("Textures/player.png");
    playerTexture.setSmooth(true);

    // Load background texture
    backgroundTexture.loadFromFile("Textures/Background.png");
    backgroundTexture.setRepeated(true);

    // Set window title
    window.setTitle("2DGame Level: " + std::to_string(currentLevel));

    // Load high scores
    levelManager.LoadHighScores();

    // Set background sprite and scale it
    background.setTexture(backgroundTexture);
    background.setScale(float(512.0f) / float(background.getTexture()->getSize().x), float(512.0f) / float(background.getTexture()->getSize().y));

    // Load level and build it
    levelManager.LoadLevel(currentLevel);
    levelManager.BuildLevel();

    // Set original size
    originalSize = sf::Vector2f(512.0f, 512.0f);

    // Create player object
    player = new Player(playerTexture, 0.02f, 120.0f, 200.0f, soundManager); // texture, animationFrames, animationSpeed, playerSpeed, jumpHeight
    player->editorMode = false;

    // Load sounds and assign to sound manager
    coinBuffer.loadFromFile("Audio/collectPoint.wav");
    coinSound.setBuffer(coinBuffer);
    soundManager.sounds.push_back(&coinSound);

    dieBuffer.loadFromFile("Audio/deadSound.wav");
    dieSound.setBuffer(dieBuffer);
    soundManager.sounds.push_back(&dieSound);

    clickBuffer.loadFromFile("Audio/click.wav");
    clickSound.setBuffer(clickBuffer);
    soundManager.sounds.push_back(&clickSound);
}

// ResetGame function
// Resets the game state to start a new level.
void GameManager::ResetGame(sf::RenderWindow& window, LevelManager& levelManager, int currentLevel) {
    // Reset high score display
    stringstream stream;
    stream << fixed << setprecision(2) << levelManager.highScores[currentLevel];
    
    // Reset game variables
    levelManager.currentTime = 0;
    levelManager.coinsCollected = 0;
    player->SetPosition(sf::Vector2f(220, 220));
    player->health = player->maxHealth;
    player->SetScale(sf::Vector2f(1, 1));
    player->facingRight = true;
    player->editorMode = false;

    // Reload and rebuild the level
    levelManager.LoadLevel(currentLevel);
    levelManager.BuildLevel();
}

// CheckInput function
// Handles all input events from the keyboard and mouse.
void GameManager::CheckInput(sf::Event& event, sf::RenderWindow& window, LevelManager& levelManager, int& currentLevel, bool& levelEditorEnabled, GUIManager& guiManager, sf::Vector2f& originalSize, sf::View& view, sf::Sprite& background, int& windowWidth, float VIEW_HEIGHT) {
    while (window.pollEvent(event)) {
        switch (event.type) {
            // Handle window closed event
            case sf::Event::Closed:
                levelManager.SaveLevel(currentLevel);
                window.close();
                break;

            // Handle window resized event
            case sf::Event::Resized:
                ResizeView(window, view, VIEW_HEIGHT);
                background.setTextureRect(sf::IntRect(0, 0, background.getTexture()->getSize().x * 3, background.getTexture()->getSize().y));
                windowWidth = window.getSize().x;
                break;

            // Handle key released event
            case sf::Event::KeyReleased:
                // Handle Escape key to open/close menu
                if (event.key.code == sf::Keyboard::Escape) {
                    guiManager.SetPanel(guiManager.Menu, sf::Vector2f(window.getSize().x / originalSize.x, window.getSize().y / originalSize.y), GetWindowSize(window));
                    player->walkSound.stop();
                }
                // Handle other key presses when not in menu
                if (!guiManager.inMenu) {
                    // Handle P key to open pause menu
                    if (event.key.code == sf::Keyboard::P) {
                        player->walkSound.stop();
                        guiManager.SetPanel(guiManager.Pause, sf::Vector2f(window.getSize().x / originalSize.x, window.getSize().y / originalSize.y), GetWindowSize(window));
                    }
                    // Handle F10 key to toggle level editor mode
                    if (event.key.code == sf::Keyboard::F10) {
                        levelEditorEnabled = !levelEditorEnabled;
                        player->editorMode = levelEditorEnabled;
                        levelManager.SaveLevel(currentLevel);
                        if (levelEditorEnabled) {
                            guiManager.SetPanel(guiManager.Editor, sf::Vector2f(window.getSize().x / originalSize.x, window.getSize().y / originalSize.y), GetWindowSize(window));
                        } else {
                            guiManager.SetPanel(guiManager.GameOverlay, sf::Vector2f(window.getSize().x / originalSize.x, window.getSize().y / originalSize.y), GetWindowSize(window));
                        }
                    }
                    // Handle key presses in level editor mode
                    if (levelEditorEnabled) {
                        // Handle numeric keys to select different tiles
                        if (event.key.code == sf::Keyboard::Num1) {
                            if (levelManager.currentTileId > 0) {
                                levelManager.currentTileId--;
                            }
                        }
                        if (event.key.code == sf::Keyboard::Num2) {
                            if (levelManager.currentTileId < 22) {
                                levelManager.currentTileId++;
                            }
                        }
                        if (event.key.code == sf::Keyboard::Num3) {
                            levelManager.currentTileId = -1;
                        }
                    }
                } else { 
					// Handle key presses when in menu
                    // Handle P key to close pause menu
                    if (event.key.code == sf::Keyboard::P) {
                        guiManager.SetPanel(guiManager.GameOverlay, sf::Vector2f(window.getSize().x / originalSize.x, window.getSize().y / originalSize.y), GetWindowSize(window));
                    }
                    // Handle arrow keys or W/S keys to navigate menu
                    if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
                        int t = guiManager.currentPanel->buttons.size() - 1;
                        if (t > guiManager.currentButton) {
                            guiManager.currentButton++;
                        }
                    }
                    if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
                        if (guiManager.currentButton > 0) {
                            guiManager.currentButton--;
                        }
                    }
                    // Handle Enter or E key to select menu option
                    if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::E) {
                        CheckButton(guiManager.GetCurrentButtonId(), window, levelManager, currentLevel, levelEditorEnabled, guiManager, originalSize);
                    }
                }
                break;

            // Handle mouse moved event
            case sf::Event::MouseMoved:
                guiManager.currentButton = -1;
                break;

            // Handle mouse button released event
            case sf::Event::MouseButtonReleased:
                // Handle left mouse button release in level editor mode
                if (!guiManager.inMenu && levelEditorEnabled) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        levelManager.CreateNewTile(window, levelManager.currentTileId);
                    }
                } else { // Handle mouse button release in menu
                    CheckButton(guiManager.GetCurrentButtonId(), window, levelManager, currentLevel, levelEditorEnabled, guiManager, originalSize);
                }
                break;
        }
    }
}

// UpdateGame function
// Updates the game state including player, UI text, and collision detection.
void GameManager::UpdateGame(sf::RenderWindow& window, GUIManager& guiManager, LevelManager& levelManager, float deltaTime, int currentLevel, sf::Vector2f& originalSize, sf::View& view, sf::Sprite& background, bool editorEnabled) {
    stringstream stream;
    stringstream streamHighscore;
    stringstream streamCoins;
    sf::Vector2f playerPos = player->GetPosition();

    // Update player and level time
    if (!guiManager.inMenu) {
        player->Update(deltaTime);
        levelManager.currentTime += deltaTime;
        stream << fixed << setprecision(2) << levelManager.currentTime;
        streamHighscore << fixed << setprecision(2) << levelManager.highScores[currentLevel];
        streamCoins << levelManager.coinsCollected;

        // Update UI text if in game overlay
        if (guiManager.CheckIfCurrentWindow(guiManager.GameOverlay)) {
            guiManager.UpdateText(0, "Time: " + stream.str());
            guiManager.UpdateText(1, "HighScore: " + streamHighscore.str());
            guiManager.UpdateText(2, "Coins: " + streamCoins.str());
        }

        // Handle player collision with tiles
        sf::Vector2f direction;
        player->grounded = false;
        for (auto& platform : levelManager.tiles) {
            if (platform->position.x > (playerPos.x - 100) && platform->position.x < (playerPos.x + 100)) {
                if (platform->tileId != 3) { // Exclude mid dirt tile
                    posOffset = sf::Vector2f(0.0f, 0.0f);
                    sf::Vector2f intersect = sf::Vector2f(0.0f, 0.0f);
                    if (platform->tileId >= 14 && platform->tileId <= 16) { // Colliding with half size tile
                        posOffset = sf::Vector2f(0.0f, 18.75f);
                    }
                    else if (platform->tileId >= 17 && platform->tileId <= 19) { // Colliding with half size tile
                        posOffset = sf::Vector2f(0.0f, -18.75f);
                    }
                    if (platform->tileId == 11 || platform->tileId == 12) { // Colliding with enemy
                        intersect = sf::Vector2f(10.0f, 10.0f);
                    }
                    if (platform->GetCollider().checkCollision(player->GetCollider(), direction, 1.0f, (-10.0f * (player->health / player->maxHealth)), (-10.0f * (player->health / player->maxHealth)), posOffset, intersect)) {
                        if (platform->tileId == 9) { // Colliding with plants
                            levelManager.coinsCollected++;
                            Coin* coin = dynamic_cast<Coin*>(platform.get());
                            coin->PickedUp(sf::Vector2f(-1000.0f, -1000.0f));
                            coinSound.play();
                            if (player->health + 4000 < player->maxHealth) {
                                player->health += 4000;
                            }
                            else {
                                player->health = player->maxHealth;
                            }
                        }
                        else if ((platform->tileId == 11 || platform->tileId == 12) && !editorEnabled) { // Colliding with enemy
                            // Game over if colliding with enemy
                            dieSound.play();
                            player->walkSound.stop();
                            guiManager.SetPanel(guiManager.GameOver, sf::Vector2f(window.getSize().x / originalSize.x, window.getSize().y / originalSize.y), GetWindowSize(window));
                        }
                        else if (platform->tileId == 10) { // Colliding with finish
                            player->walkSound.stop();
                            // End game and check highscore if colliding with finish
                            if (levelManager.UpdateHighscore(currentLevel, (100 - levelManager.currentTime) + levelManager.coinsCollected - player->health / 10)) {
                                levelManager.SaveHighScores();
                                std::cout << "new highscore\n";
                            }
                            guiManager.SetPanel(guiManager.LevelFinished, sf::Vector2f(window.getSize().x / originalSize.x, window.getSize().y / originalSize.y), GetWindowSize(window));
                        }
                        else {
                            // Colliding with normal wall/ground
                            player->inColdZone = (platform->tileId >= 20 && platform->tileId <= 22);
                            player->OnCollision(direction);
                        }
                        if (direction.y < 0.0f) {
                            player->grounded = true;
                        }
                    }
                }
            }
        }

        // Show game over window when player is dead
        if (playerPos.y < 450 && player->health > 1) {
            view.setCenter(playerPos);
        }
        else {
            if (player->health > 10) {
                view.setCenter(playerPos.x, 450);
                if (playerPos.y > 900) {
                    dieSound.play();
                    player->walkSound.stop();
                    guiManager.SetPanel(guiManager.GameOver, sf::Vector2f(window.getSize().x / originalSize.x, window.getSize().y / originalSize.y), GetWindowSize(window));
                }
            }
            else {
                dieSound.play();
                player->walkSound.stop();
                guiManager.SetPanel(guiManager.GameOver, sf::Vector2f(window.getSize().x / originalSize.x, window.getSize().y / originalSize.y), GetWindowSize(window));
            }
        }
    }
    else { // Update LevelFinished window
        if (guiManager.CheckIfCurrentWindow(guiManager.LevelFinished)) {
            stringstream streamScore;
            stream << fixed << setprecision(2) << levelManager.currentTime;
            streamHighscore << fixed << setprecision(2) << levelManager.highScores[currentLevel];
            streamCoins << levelManager.coinsCollected;
            streamScore << fixed << setprecision(2) << ((100 - levelManager.currentTime) + levelManager.coinsCollected - player->health / 10);
            guiManager.UpdateText(0, "Time: " + stream.str());
            guiManager.UpdateText(1, "HighScore: " + streamHighscore.str());
            guiManager.UpdateText(2, "Plants: " + streamCoins.str());
            guiManager.UpdateText(3, "Score: " + streamScore.str());
        }
    }
    background.setPosition(window.mapPixelToCoords(sf::Vector2i(0, 0)));
}

// CheckButton function
// Checks which button is pressed or selected in the menu and performs corresponding actions.
void GameManager::CheckButton(int currentButtonId, sf::RenderWindow& window, LevelManager& levelManager, int& currentLevel, bool& levelEditorEnabled, GUIManager& guiManager, sf::Vector2f& originalSize) {
    if (currentButtonId != 0) {
        clickSound.play();
    }
    switch (currentButtonId) {
    case 1: // Start button on menu
        ResetGame(window, levelManager, currentLevel);
        guiManager.SetPanel(guiManager.GameOverlay, sf::Vector2f(window.getSize().x / originalSize.x, window.getSize().y / originalSize.y), GetWindowSize(window));
        break;
    case 2: // Exit application
        levelManager.SaveLevel(currentLevel);
        window.close();
        break;
    case 3: // Load next level
        if (currentLevel < 3) {
            currentLevel++;
            levelEditorEnabled = false;
            ResetGame(window, levelManager, currentLevel);
            guiManager.SetPanel(guiManager.GameOverlay, sf::Vector2f(window.getSize().x / originalSize.x, window.getSize().y / originalSize.y), GetWindowSize(window));
        }
        else {
            guiManager.SetPanel(guiManager.Menu, sf::Vector2f(window.getSize().x / originalSize.x, window.getSize().y / originalSize.y), GetWindowSize(window));
            if (soundManager->currentVolume > 1.0f) {
                guiManager.currentPanel->buttons[6]->SetButtonText("Sounds Off!");
            }
            else {
                guiManager.currentPanel->buttons[6]->SetButtonText("Sounds On!");
            }
        }
        break;
    case 4: // Restart level
        levelEditorEnabled = false;
        ResetGame(window, levelManager, currentLevel);
        guiManager.SetPanel(guiManager.GameOverlay, sf::Vector2f(window.getSize().x / originalSize.x, window.getSize().y / originalSize.y), GetWindowSize(window));
        break;
    case 5: // Load menu
        guiManager.SetPanel(guiManager.Menu, sf::Vector2f(window.getSize().x / originalSize.x, window.getSize().y / originalSize.y), GetWindowSize(window));
        if (soundManager->currentVolume > 1.0f) {
            guiManager.currentPanel->buttons[6]->SetButtonText("Sounds Off!");
        }
        else {
            guiManager.currentPanel->buttons[6]->SetButtonText("Sounds On!");
        }
        break;
    case 6: // Load level
        levelEditorEnabled = false;
        currentLevel = guiManager.GetSelectedLevel();
        ResetGame(window, levelManager, currentLevel);
        guiManager.SetPanel(guiManager.GameOverlay, sf::Vector2f(window.getSize().x / originalSize.x, window.getSize().y / originalSize.y), GetWindowSize(window));
        break;
    case 7: // Show levels
        guiManager.SetPanel(guiManager.Levels, sf::Vector2f(window.getSize().x / originalSize.x, window.getSize().y / originalSize.y), GetWindowSize(window));
        break;
    case 8: // Continue
        guiManager.SetPanel(guiManager.GameOverlay, sf::Vector2f(window.getSize().x / originalSize.x, window.getSize().y / originalSize.y), GetWindowSize(window));
        break;
    case 9: // Credits page
        guiManager.SetPanel(guiManager.Credits, sf::Vector2f(window.getSize().x / originalSize.x, window.getSize().y / originalSize.y), GetWindowSize(window));
        break;
    case 10: // Open URL to documentation
        cout << "Opening GitHub..." << endl;
        system("open https://github.com/ThuraAung1601/EcoVsPolluto");
        break;
    case 11: // Open URL to tutorial page
        cout << "Opening tutorial page..." << endl;
        system("open https://www.youtube.com/playlist?list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9");
        break;
    case 13: // Control page
        guiManager.SetPanel(guiManager.Controls, sf::Vector2f(window.getSize().x / originalSize.x, window.getSize().y / originalSize.y), GetWindowSize(window));
        break;
    case 14: // Toggle between fullscreen and windowed
        fullscreen = !fullscreen;
        break;
    case 15: // Toggle sounds
        if (soundManager->currentVolume <= 1.0f) {
            soundManager->SetVolume(100.0f);
            guiManager.currentPanel->buttons[6]->SetButtonText("Sounds Off!");
        }
        else {
            soundManager->SetVolume(0.0f);
            guiManager.currentPanel->buttons[6]->SetButtonText("Sounds On!");
        }
        break;
    }
}

// ResizeView function
// After changing the window size, updates the view so everything keeps its aspect ratio.
void GameManager::ResizeView(sf::RenderWindow& window, sf::View& view, float VIEW_HEIGHT) {
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

// GetWindowSize function
// Returns the window size.
sf::Vector2f GameManager::GetWindowSize(sf::RenderWindow& window) {
    return sf::Vector2f(window.getSize().x, window.getSize().y);
}