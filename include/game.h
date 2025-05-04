#pragma once

#include "bulletInteraction.h"
#include <SFML/Graphics.hpp>
#include <memory>

class MainGame {
public:
    MainGame(int windowSizeX, int windowSizeY);
    ~MainGame() = default;
    void run();
    
private:
    void handleInput();
    void render();
    bool validMove(int x, int y) const;
    void update();

    std::unique_ptr<sf::RenderWindow> window;
    Tank player;
    Map tileMap;
    
    int startTankX;
    int startTankY;

    bool upPressed = false;
    bool downPressed = false;
    bool leftPressed = false;
    bool rightPressed = false;
    bool spacePressed = false;
    

    const int tileSize = 32;
    bool moveQueued = false;
    int windowSizeX, windowSizeY;

    sf::Clock gameClock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    const sf::Time timePerFrame = sf::seconds(1.f/60.f);
};