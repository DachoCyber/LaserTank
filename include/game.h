#pragma once

#include "bulletInteraction.h"
#include <SFML/Graphics.hpp>
#include <memory>

class MainGame {
public:
    MainGame(int windowSizeX, int windowSizeY, int level);
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



    void setTrack();
    void handlTransportableTrack(int x, int y);

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

    bool killPlayer = false;
    bool bulletFired = false;

    bool returnFromTrack = false;

    std::vector<Bullet*> bullets;
    sf::Clock gameClock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    const sf::Time timePerFrame = sf::seconds(1.f/60.f);

    sf::Font weirdFont;
    sf::Text gameOverText;


    sf::Texture gobletTexture;
    sf::Sprite gobletSprite;

    std::vector<std::vector<std::vector<int>>> mapStates;

    bool playerMoved = false;
    int moveCount = 0;
    std::vector<std::pair<int, int>> playerPositions;
    int coordXKillerTank, coordYKillerTank;

    
};
