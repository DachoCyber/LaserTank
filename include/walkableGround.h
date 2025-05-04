#pragma once

#include "tile.h"

#include <SFML/Graphics.hpp>
#include <iostream>

class WalkableGround : public Tile {
public:
    WalkableGround(int x, int y) : Tile(x, y) {
        try {
            walkable = true;
            if(!tex.loadFromFile("/home/dalibor/Desktop/LaserTank/Images/walkableGround.png")) {
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
        return true;
    }
    bool isBulletDestroyable() override {
        return false;
    }
};

