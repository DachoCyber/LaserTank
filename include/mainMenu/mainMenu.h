#pragma once

#include "level.h"
#include "quit.h"
#include "start.h"
#include <memory>
#include <iostream>

class MainMenu : public sf::Drawable {
private:
    Level levels;
    Start start;
    Quit quit;
    static constexpr int menuWindowSizeX = 300;
    static constexpr int menuWindowSizeY = 300;
    std::unique_ptr<sf::RenderWindow> window;

public:
    int level;

    MainMenu(int levelCount)
        : levels(menuWindowSizeX, menuWindowSizeY, levelCount),
          start(menuWindowSizeX, menuWindowSizeY),
          quit(menuWindowSizeX, menuWindowSizeY),
          level(-1),
          window(std::make_unique<sf::RenderWindow>(
              sf::VideoMode(menuWindowSizeX, menuWindowSizeY), "Laser Tank", sf::Style::Default)) {}

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(levels);
        target.draw(start);
        target.draw(quit);
    }

    void run() {
        while (window->isOpen()) {
            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window->close();
                }

                if (event.type == sf::Event::MouseButtonPressed &&
                    event.mouseButton.button == sf::Mouse::Left) {
                    
                    sf::Vector2f mousePos = window->mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                    levels.handleClick(mousePos);
                    start.handleClick(mousePos);
                }
            }

            if (levels.level != -1) {
                level = levels.level;
                window->close();
                break;
            }

            render();
        }
    }

    void render() {
        window->clear(sf::Color::Black);
        window->draw(levels);
        window->draw(start);
        window->draw(quit);
        window->display();
    }

    int getChosenLevel() const {
        return level;
    }
};
