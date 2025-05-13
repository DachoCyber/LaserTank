#pragma once

#include "bulletInteraction.h"
#include <SFML/Graphics.hpp>
#include <memory>

class MainGame {
public:
    MainGame(int windowSizeX, int windowSizeY, int playerPosX, int playerPosY, int level);
    ~MainGame() = default;
    void run();
    
    

private:
    void loadGoblet();
    void drawGoblet();

    void loadGameOverFont();

    bool gameEnd();
    bool gameLost();
    bool gameWon();
    bool shouldEnemyFireBullet();
    bool playerKilledByEnemy();

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

    bool killPlayer = false;
    bool bulletFired = false;

    Bullet* bullet;
    sf::Clock gameClock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    const sf::Time timePerFrame = sf::seconds(1.f/60.f);

    sf::Font weirdFont;
    sf::Text gameOverText;


    sf::Texture gobletTexture;
    sf::Sprite gobletSprite;
};
