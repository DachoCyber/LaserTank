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
            sprite.setPosition(x, y);
            sprite.setScale(32.f/55.f, 32.f/55.f);
        }
        catch(const std::string& what) {
            std::cerr << what << std::endl;
        }
    }
    bool isWalkable() override {
        return true;
    }
    bool isBulletDestroyable() override {
        return false;
    }
    void interactWithBullet(Direction dir) override {
        return;
    }
    bool isBulletMovable() override {
        return false;
    }
    virtual int getMirrorType() {
        return 0;
    }
    bool isMirror1() override {
        return false;
    }
    bool isMirror2() override {
        return false;
    }
    bool isMirror3() override {
        return false;
    }bool isMirror4() override {
        return false;
    }
    bool isOverlappled() override {
        return true;
    }
};

