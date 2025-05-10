#pragma once

#include "tile.h"
#include <iostream>


class Mirror3Tile : public Tile {

    private:
        const sf::Texture* texturePtr;
    public:
        Mirror3Tile(int x, int y, const sf::Texture& mirrorTex) : Tile(x, y) {
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
        return false;
    }
    bool isMirror3() override {
        return true;
    }
    bool isMirror4() override {
        return false;
    }
    bool isOverlappled() override {
        return false;
    }
    int getMirrorType() override {
        return 3;
    }
    virtual bool killPlayerTile(int playerPosX, int playerPosY) override {
        return false;
    }
    bool isWater() override {
        return false;
    }
    bool isUnderWater(const std::vector<std::pair<int, int>>& waterTileCoords) override {
        return false;
    }
    void setAlpha(int alpha) override {
        sf::Color color = sprite.getColor();
        color.a = alpha;
        sprite.setColor(color);
    }
};