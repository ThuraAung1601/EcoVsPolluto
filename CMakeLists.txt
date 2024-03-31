cmake_minimum_required(VERSION 3.10)
project(EcoVsPolluto)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Add all source files to the executable
add_executable(app 
    ./EcoVsPolluto/main.cpp
    ./EcoVsPolluto/Animation.cpp
    ./EcoVsPolluto/Button.cpp
    ./EcoVsPolluto/GUIManager.cpp
    ./EcoVsPolluto/GameManager.cpp
    ./EcoVsPolluto/Particle.cpp
    ./EcoVsPolluto/ParticleSystem.cpp
    ./EcoVsPolluto/Player.cpp
    ./EcoVsPolluto/SoundManager.cpp
    ./EcoVsPolluto/LevelManager.cpp
    ./EcoVsPolluto/Tile.cpp
    ./EcoVsPolluto/Panel.cpp
    ./EcoVsPolluto/Text.cpp
    ./EcoVsPolluto/Collider.cpp
)

# Include SFML
find_package(SFML 2.5.1 COMPONENTS graphics window system audio network REQUIRED)

# Link SFML libraries
target_link_libraries(app sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
