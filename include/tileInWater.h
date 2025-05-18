#pragma once

#include "tile.h"


class TileInWater : public Tile {
public:
    TileInWater(int x, int y) : Tile(x, y) {
        try {
            walkable = true;
            isMovable = false;
            overlappled = true;
            if(!tex.loadFromFile("/home/dalibor/Desktop/LaserTank/Images/tileInWater.png")) {
               throw new std::runtime_error("Cannot open image tileInWater.png!");
            }
            sprite.setTexture(tex);
            sprite.setPosition(x, y);
            posX = x;
            posY = y;
        }
        catch(const std::string& what) {
            std::cerr << what << std::endl;
        }
    }
    bool overlappled;
    bool isMovable;
    virtual bool killPlayerTile(int playerPosX, int playerPosY) override {
        return false;
    }
    bool isUnderWater(const std::vector<std::pair<int, int>>& waterTileCoords) override {

        return true;
    }
    void setAlpha(int alpha) override {
        sf::Color color = sprite.getColor();
        color.a = alpha;
        sprite.setColor(color);
    }
    bool isWalkable() override {

        return walkable;
    }
    bool isBulletDestroyable() override {
        return false;
    }
    void interactWithBullet(Direction dir) override {
        return;
    }
    bool isBulletMovable() override {
        return true;
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
        return overlappled;
    }
    bool isWater() override {
        return false;
    }
    bool isTileMovableBlock() {
        return isMovable;
    }
    bool isUndestructibleBlock() override {
        return false;
    }
    bool killPlayer(const std::vector<std::vector<std::unique_ptr<Tile>>>& tileMap, int playerPosX, int playerPosY) override {
        return false;
    }
    bool fireBullet() override {
        return false;
    }
};