#pragma once

#include "tile.h"


class MovableBlock : public Tile {
public:
    MovableBlock(int x, int y) : Tile(x, y) {
        try {
            walkable = false;
            isMovable = true;
            overlappled = false;
            if(!tex.loadFromFile("/home/dalibor/Desktop/LaserTank/Images/MovableBlock.png")) {
               throw new std::runtime_error("Cannot open image walkableGround.png!");
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
        if (waterTileCoords.empty()) return false; // Early exit if no water tile
        for (const auto& coord : waterTileCoords) {
            if (coord.first == posY/tileSize && coord.second == posX/tileSize) {
                walkable = true;
                isMovable = false;
                overlappled = true;
                return true;
            }
        }
        return false;
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
};