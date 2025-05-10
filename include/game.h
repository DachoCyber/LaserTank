#pragma once

#include "bulletInteraction.h"
#include <SFML/Graphics.hpp>
#include <memory>

class MainGame {
public:
    MainGame(int windowSizeX, int windowSizeY, int playerPosX, int playerPosY);
    ~MainGame() = default;
    void run();
    
private:
    void handleInput();
    void render();
    void update();

    std::unique_ptr<sf::RenderWindow> window;
    Tank player;
    Map tileMap;
    
    int startTankX;
    int startTankY;

    int countSpacePressed;

    const int tileSize = 32;
    bool moveQueued = false;
    int windowSizeX, windowSizeY;

    int playerPosX, playerPosY;

    sf::Clock gameClock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    const sf::Time timePerFrame = sf::seconds(1.f/60.f);
};
