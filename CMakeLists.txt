cmake_minimum_required(VERSION 3.10)
project(EcoVsPolluto)

# Set SFML path
set(SFML_PATH "/opt/homebrew/Cellar/sfml/2.6.1")

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Find all source files
file(GLOB_RECURSE SOURCES "*.cpp")

# Include SFML
include_directories(${SFML_PATH}/include)
link_directories(${SFML_PATH}/lib)

# Create executable
add_executable(app ${SOURCES})

# Link SFML libraries
target_link_libraries(app sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
