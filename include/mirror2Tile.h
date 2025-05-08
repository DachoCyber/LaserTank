#pragma once

#include "tile.h"
#include <iostream>


class Mirror2Tile : public Tile {

    private:
        const sf::Texture* texturePtr;
    public:
        Mirror2Tile(int x, int y, const sf::Texture& mirrorTex) : Tile(x, y) {
            walkable = false;
            texturePtr = &mirrorTex;
            sprite.setTexture(*texturePtr);
            sprite.setPosition(x, y);
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
    void interactWithBullet(Direction dir) override {
        return;
    }
    bool isMirror1() override {
        return false;
    }
    bool isMirror2() override {
        return true;
    }
    bool isMirror3() override {
        return false;
    }
    bool isMirror4() override {
        return false;
    }
    bool isOverlappled() override {
        return false;
    }
    int getMirrorType() override {
        return 2;
    }
};