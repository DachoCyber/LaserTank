#pragma once

#include "tile.h"

#include <SFML/Graphics.hpp>
#include <iostream>

class DestructibleBlock : public Tile {
private:
    sf::Texture destructibleBlockTex;
    sf::Sprite destructibleBlockSprite;
public:
    DestructibleBlock(int x, int y) :Tile(x, y) {
        try {
            walkable = false;
            if(!tex.loadFromFile("/home/dalibor/Desktop/LaserTank/Images/destructibleBlock.png")) {
               throw new std::runtime_error("Cannot open image walkableGround.png!");
            }
            sprite.setTexture(tex);
            sprite.setPosition(x*2, y*2);
        }
        catch(std::string& what) {
            std::cerr << what << std::endl;
        }
    }
    bool isWalkable() override {
        return false;
    }
    bool isBulletDestroyable() override {
        return true;
    }
};

