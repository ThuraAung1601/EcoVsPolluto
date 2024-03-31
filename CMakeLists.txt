cmake_minimum_required(VERSION 3.10)
project(EcoVsPolluto)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Add main.cpp as the only source file
add_executable(app main.cpp)

# Include SFML
find_package(SFML 2.5.1 COMPONENTS graphics window system audio network REQUIRED)

# Link SFML libraries
target_link_libraries(app sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
