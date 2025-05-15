#pragma once

#include "tile.h"
#include <iostream>


class TransportTrack : public Tile {
    public:
        TransportTrack(int x, int y, Direction dir) : Tile(x, y) {
            try {
                walkable = true;
                switch(dir) {
                    case LEFT :
                        if(!tex.loadFromFile("/home/dalibor/Desktop/LaserTank/Images/transportTrack.png")) {
                            throw new std::runtime_error("Cannot open image walkableGround.png!");
                        }
                        break;
                    case RIGHT :
                        if(!tex.loadFromFile("/home/dalibor/Desktop/LaserTank/Images/transportTrack2.png")) {
                            throw new std::runtime_error("Cannot open image walkableGround.png!");
                        }
                        break;
                    case UP :
                        if(!tex.loadFromFile("/home/dalibor/Desktop/LaserTank/Images/transportTrack3.png")) {
                            throw new std::runtime_error("Cannot open");
                        }
                        break;
                    case DOWN :
                        if(!tex.loadFromFile("/home/dalibor/Desktop/LaserTank/Images/transportTrack4.png")) {
                            throw new std::runtime_error("Cannot open");
                        }
                        break;
                }
                sprite.setTexture(tex);
                sprite.setPosition(x, y);
           
                this->dir = dir;
            }
        catch(const std::string& what) {
            std::cerr << what << std::endl;
        }
    }
    Direction dir;
    bool isUndestructibleBlock() override {
        return false;
    }
    bool fireBullet() override {
        return false;
    }
    bool killPlayer(const std::vector<std::vector<std::unique_ptr<Tile>>>& tileMap, int playerPosX, int playerPosY) override {
        return false;
    }
    void setAlpha(int alpha) override {
        sf::Color waterColor = sprite.getColor();
        waterColor.a = alpha;
        sprite.setColor(sf::Color(waterColor));
    }
    bool killPlayerTile(int playerPosX, int playerPosY) override {
        if(posX == playerPosX && posY == playerPosY) {
            return true;
        }
        return false;
    }
    bool isWater() override {
        return false;
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
        return true;
    }
    int getMirrorType() override {
        return -1;
    }
    bool isUnderWater(const std::vector<std::pair<int, int>>& waterTileCoords) override {
        return false;
    }
    int isTransportTrack() {
        int returnValue = 0;
        switch(dir) {
            case LEFT:
                returnValue = 1;
                break;
            case RIGHT:
                returnValue = 2;
                break;
            case UP:
                returnValue = 3;
                break;
            case DOWN:
                returnValue = 4;
                break;
        }
        return returnValue;
    }
};