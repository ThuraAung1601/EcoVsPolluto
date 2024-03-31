cmake_minimum_required(VERSION 3.10)
project(EcoVsPolluto CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# List all source files
file(GLOB_RECURSE SOURCES "*.cpp")

# Remove CMake-generated files from the list of sources
file(GLOB_RECURSE REMOVE_CMAKE "cmake-build-debug/*")
list(REMOVE_ITEM SOURCES ${REMOVE_CMAKE})

# Include SFML
find_package(SFML 2.5.1 COMPONENTS graphics window system audio network REQUIRED)

# Create executable
add_executable(app ${SOURCES})

# Link SFML libraries
target_link_libraries(app sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
