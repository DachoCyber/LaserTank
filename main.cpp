#include <SFML/Graphics.hpp>
#include "include/player.h"
#include "include/map.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(608, 608), "Laser Tank", sf::Style::Close);
    window.setFramerateLimit(60);
    

    Tank tank(96, 96, 608, 608); 

    Map mapTerrain;

    sf::Clock clock;
    sf::Time accumulatedTime = sf::Time::Zero;
    const sf::Time updateInterval = sf::milliseconds(1);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }   

        accumulatedTime += clock.restart();

        tank.handleInput();
        tank.update(accumulatedTime, updateInterval);



        window.clear(sf::Color::White);
        
        window.draw(mapTerrain);
        window.draw(tank);
        window.display();
    }

    return 0;
}
