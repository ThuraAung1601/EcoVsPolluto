cmake_minimum_required(VERSION 3.10)
project(EcoVsPolluto)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Find all source files
file(GLOB_RECURSE SOURCES "*.cpp")

# Include SFML
find_package(SFML 2.6 COMPONENTS graphics window system audio network REQUIRED)

# Create executable
add_executable(app ${SOURCES})

# Link SFML libraries
target_link_libraries(app sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
