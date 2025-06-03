#pragma once

#include "level.h"
#include "quit.h"
#include "start.h"
#include "editor.h"
#include <memory>
#include <iostream>

class MainMenu : public sf::Drawable {
private:
    Level levels;
    Start start;
    Editor editor;
    static constexpr int menuWindowSizeX = 450;
    static constexpr int menuWindowSizeY = 450;
    std::vector<std::vector<int>> tileMap;
    std::unique_ptr<sf::RenderWindow> window;

    bool editorWinClose = false;

public:
    int level;

    MainMenu(int levelCount)
        : levels(menuWindowSizeX, menuWindowSizeY, levelCount),
          start(menuWindowSizeX, menuWindowSizeY),
          editor(menuWindowSizeX, menuWindowSizeY, editorWinClose),
          level(-1),
          window(std::make_unique<sf::RenderWindow>(
              sf::VideoMode(menuWindowSizeX, menuWindowSizeY), "Laser Tank", sf::Style::Default)) {}

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(levels);
        target.draw(start);
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
                    editor.button.handleClick(mousePos);
                }
            }

            if (start.wasClicked() && levels.level != -1) {
                level = levels.level;
                window->close();
                break;
            }
            if(editor.button.wasClicked()) {
                editor.handleClick();
            }

            render();
        }
    }

    void render() {
        window->clear(sf::Color::Black);
        window->draw(levels);
        window->draw(start);
        window->draw(editor);
        window->display();
    }

    int getChosenLevel() const {
        return level;
    }
};
