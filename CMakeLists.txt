cmake_minimum_required(VERSION 3.10)
project(EcoVsPolluto)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# List all source files except CMakeCXXCompilerId.cpp
set(SOURCES
    main.cpp
    Animation.cpp
    Button.cpp
    GUIManager.cpp
    GameManager.cpp
    Particle.cpp
    ParticleSystem.cpp
    Player.cpp
    SoundManager.cpp
    LevelManager.cpp
    Tile.cpp
    Panel.cpp
    Text.cpp
    Collider.cpp
)

# Include SFML
find_package(SFML 2.5.1 COMPONENTS graphics window system audio network REQUIRED)

# Create executable
add_executable(app ${SOURCES})

# Link SFML libraries
target_link_libraries(app sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
