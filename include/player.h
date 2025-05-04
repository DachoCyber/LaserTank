#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include "bullet.h"
#include "direction.h" 
#include "map.h"

class Tank : public sf::Drawable {
public:
    Tank(int startX, int startY, int windowSizeX, int windowSizeY);
    virtual ~Tank() = default; 
    void setDir(Direction dir);
    Direction getDir() const;

    void handleInput();
    void update(sf::Time, sf::Time);
    sf::Vector2i getGridPosition() const;
    void setGridPosition(sf::Vector2i);
    bool validMove(int x, int y) const;
    void fireBullet();
    Bullet* getBullet() const {return  bullet;}
    bool bulletInScreen() const;
    void loadTextureFromImage();
    void updateSpritePosition();
    void deleteBullet();
private:

    bool upPressed = false;
    bool downPressed = false;
    bool leftPressed = false;
    bool rightPressed = false;


    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    Bullet* bullet = nullptr;

    sf::Image tankImg;
    sf::Texture texture;
    sf::Sprite sprite;

    Direction dir;
    sf::Vector2i gridPos;
    bool moveQueued = false;
    const int tileSize = 32;

    int windowSizeX, windowSizeY;
};
