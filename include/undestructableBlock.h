#pragma once

#include "tile.h"

class UndestructableBlock : public Tile {
public:
    UndestructableBlock(int x, int y) : Tile(x, y) {
        try {
            walkable = true;
            if(!tex.loadFromFile("/home/dalibor/Desktop/LaserTank/Images/undestructibleBlock.png")) {
               throw new std::runtime_error("Cannot open image undestructibleBlock.png!");
            }
            sprite.setTexture(tex);
            sprite.setPosition(x, y);
        }
        catch(const std::string& what) {
            std::cerr << what << std::endl;
        }
    }
    virtual bool isUnderWater(const std::vector<std::pair<int, int>>& waterTileCoords) {
        return false;
    }
    bool isUndestructibleBlock() override {
        return true;
    }
    virtual bool killPlayerTile(int playerPosX, int playerPosY) override {
        return false;
    }
    void setAlpha(int alpha) override {
        sf::Color color = sprite.getColor();
        color.a = alpha;
        sprite.setColor(color);
    }
    bool isWalkable() override {
        return false;
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
        return false;
    }
    bool isWater() override {
        return false;
    }
    bool killPlayer(const std::vector<std::vector<std::unique_ptr<Tile>>>& tileMap, int playerPosX, int playerPosY) override {
        return false;
    }
    bool fireBullet() override {
        return false;
    }
};