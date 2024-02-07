#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "Hello world!");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        // Draw anything here if needed
        window.display();
    }

    return 0;
}

// g++ test.cpp -I/opt/homebrew/Cellar/sfml/2.6.1/include -o a -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
