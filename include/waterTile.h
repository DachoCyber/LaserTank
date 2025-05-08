#pragma once

#include "tile.h"
#include <iostream>


class WaterTile : public Tile {

    private:
        const sf::Texture* texturePtr;
    public:
        WaterTile(int x, int y, const sf::Texture& WaterTileTexture) : Tile(x, y) {
            walkable = false;
            texturePtr = &WaterTileTexture;
            sprite.setTexture(*texturePtr);
            sprite.setPosition(x, y);
        }


    bool killPlayerTile(int playerPosX, int playerPosY) override {
        if(posX == playerPosX && posY == playerPosY) {
            return true;
        }
        return false;
    }
    bool isWater() override {
        return true;
    }

    bool isWalkable() override {
        return true;
    }
    bool isBulletDestroyable() override {
        return false;
    }
    bool isBulletMovable() override {
        return false;
    }
    void interactWithBullet(Direction dir) override {
        return;
    }
    bool isMirror1() override {
        return false;
    }
    bool isMirror2() override {
        return false;
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
        return -1;
    }
};