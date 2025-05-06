#pragma once

#include "tile.h"
#include <iostream>


class Mirror1Tile : public Tile {
public:
    Mirror1Tile(int x, int y) : Tile(x, y) {
        try {
            walkable = false;
            if(!tex.loadFromFile("/home/dalibor/Desktop/LaserTank/Images/Mirror1.png")) {
               throw new std::runtime_error("Cannot open image walkableGround.png!");
            }
            sprite.setTexture(tex);
            sprite.setPosition(x, y);
        }
        catch(const std::string& what) {
            std::cerr << what << std::endl;
        }
    }

    bool isWalkable() override {
        return false;
    }
    bool isBulletDestroyable() override {
        return false;
    }
    bool isBulletMovable() override {
        return true;
    }
    void interactWithBullet() override {
        return;
    }
};