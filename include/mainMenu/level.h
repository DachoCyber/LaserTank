#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "resources.h"

class Level : public sf::Drawable {
private:
    sf::RectangleShape levelRectShape;
    sf::RectangleShape paddingMenu;
    bool menuWindowOpen = false;
    int levelCount;
    int menuSizeX;
    int menuSizeY;

private:
    int openMenuWindow() {
        menuWindowOpen = true;

        sf::RenderWindow menuWindow(sf::VideoMode(menuSizeX, levelCount * 50), "Choose Level");

        std::vector<sf::RectangleShape> levelButtons(levelCount);
        std::vector<sf::Text> levelTexts(levelCount);
        /*if (!font.loadFromFile("arial.ttf")) {
            return -1;
        }*/

        for (int i = 0; i < levelCount; ++i) {
            levelButtons[i].setSize(sf::Vector2f(static_cast<float>(menuSizeX/2), 50.f));
            levelButtons[i].setFillColor(sf::Color(150, 150, 250));
            levelButtons[i].setPosition(0.f, static_cast<float>(i * 50));

            levelTexts[i].setFont(globalFont);
            levelTexts[i].setCharacterSize(24);
            levelTexts[i].setString("Level " + std::to_string(i + 1));
            levelTexts[i].setFillColor(sf::Color::Black);
            levelTexts[i].setPosition(levelButtons[i].getPosition().x + 20.f, levelButtons[i].getPosition().y + 10.f);
        }

        while (menuWindow.isOpen()) {
            sf::Event event;
            while (menuWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    menuWindow.close();
                    menuWindowOpen = false;
                }

                if (event.type == sf::Event::MouseButtonPressed &&
                    event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = menuWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                    for (int i = 0; i < levelButtons.size(); ++i) {
                        if (levelButtons[i].getGlobalBounds().contains(mousePos)) {
                            menuWindow.close();
                            menuWindowOpen = false;
                            level = i + 1;
                            std::cout << level << std::endl;
                            return i;
                        }
                    }
                }
            }

            menuWindow.clear(sf::Color::White);
            for (int i = 0; i < levelButtons.size(); ++i) {
                menuWindow.draw(levelButtons[i]);
                menuWindow.draw(levelTexts[i]);
            }
            menuWindow.display();
        }

        return -1;
    }

public:
    int level;

    Level(int menuWinSizeX, int menuWinSizeY, int levelCount)
        : menuSizeX(menuWinSizeX),
          menuSizeY(menuWinSizeY),
          levelCount(levelCount),
          level(-1)
    {
        levelRectShape.setSize(sf::Vector2f(static_cast<float>(menuSizeX)*6/15, static_cast<float>(menuSizeY)/5));
        levelRectShape.setFillColor(sf::Color::White);
        levelRectShape.setOutlineThickness(5.f);
        levelRectShape.setPosition(sf::Vector2f((static_cast<float>(menuSizeX)) / 3, (static_cast<float>(menuSizeY*9)/15)));
        std::cout << levelRectShape.getSize().x << std::endl;
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(levelRectShape);
    }

    void handleClick(const sf::Vector2f& mousePos) {
        if (levelRectShape.getGlobalBounds().contains(mousePos) && !menuWindowOpen) {
            openMenuWindow();
            menuWindowOpen = true;
        }
    }
};
