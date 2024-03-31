cmake_minimum_required(VERSION 3.10)
project(EcoVsPolluto)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Find all source files
file(GLOB_RECURSE SOURCES "*.cpp")

# Add executable
add_executable(app ${SOURCES})

# Find SFML
find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system audio network)

# If SFML is not found, you can provide its path manually
if(NOT SFML_FOUND)
    set(SFML_INCLUDE_DIR "/opt/homebrew/Cellar/sfml/2.6.1/include")
    set(SFML_LIBRARY_DIR "/opt/homebrew/Cellar/sfml/2.6.1/lib")
    set(SFML_LIBRARIES "sfml-graphics" "sfml-window" "sfml-system" "sfml-audio" "sfml-network")
    include_directories(${SFML_INCLUDE_DIR})
    link_directories(${SFML_LIBRARY_DIR})
    target_link_libraries(app ${SFML_LIBRARIES})
else()
    target_link_libraries(app sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
endif()
