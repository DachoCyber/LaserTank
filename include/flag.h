#pragma once

#include "tile.h"

class Flag : public Tile {
public:
    Flag(int x, int y) : Tile(x, y) {
        try {
            if(!tex.loadFromFile("/home/dalibor/Desktop/LaserTank/Images/flagWithBackground.png")) {
               throw new std::runtime_error("Cannot open image flagWithBackground.png!");
            }
        } 
        catch(const std::string& what) {
            std::cerr << what << std::endl;
        }
        sprite.setTexture(tex);
        sprite.setPosition(x, y);
        sprite.setScale(32.f/571.f, 32.f/574.f);
    }
    bool isUndestructibleBlock() override {
        return false;
    }
    bool fireBullet() override {
        return false;
    }
    bool killPlayer(const std::vector<std::vector<std::unique_ptr<Tile>>>& tileMap, int playerPosX, int playerPosY) override {
        return false;
    }
    virtual ~Flag() = default;
    virtual bool isUnderWater(const std::vector<std::pair<int, int>>& waterTileCoords) {
        return false;
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
        return false;
    }
    bool isWater() override {
        return false;
    }
};