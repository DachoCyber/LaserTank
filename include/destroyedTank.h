    #pragma once

    #include "tile.h"
    #include "bullet.h"

    #include <memory>

    class DestroyedTank: public Tile {
    public:
        int dir;
        DestroyedTank(int x, int y, int dir) : Tile(x, y) {
            try {
                this-> dir = dir;
                walkable = false;
                switch(dir) {
                    case 0 :
                        if(!tex.loadFromFile("/home/dalibor/Desktop/LaserTank/Images/destroyedTank1.png")) {
                        throw new std::runtime_error("Cannot open image walkableGround.png!");
                        }
                        break;
                    case 1 :
                        if(!tex.loadFromFile("/home/dalibor/Desktop/LaserTank/Images/destroyedTank2.png")) {
                            throw new std::runtime_error("Cannot open image tank2.png!");
                        }
                        break;
                    case 2 :
                        if(!tex.loadFromFile("/home/dalibor/Desktop/LaserTank/Images/destroyedTank3.png")) {
                            throw new std::runtime_error("Cannot open image tank3.png!");
                        }
                        break;
                    case 3 : 
                        if(!tex.loadFromFile("/home/dalibor/Desktop/LaserTank/Images/destroyedTank4.png")) {
                            throw new std::runtime_error("Cannot open image tank4.png!");
                        }
                        break;
                }
                sprite.setTexture(tex);
                sprite.setPosition(x, y);
            }
            catch(const std::string& what) {
                std::cerr << what << std::endl;
            }
        }

        Bullet* enemysTankBullet;



        bool shouldKillPlayer = false;


        bool killPlayer(const std::vector<std::vector<std::unique_ptr<Tile>>>& tileMap, int playerPosX, int playerPosY) override {
            
            return false;
        }
        int isTank() {
            return 0;
        }

        Bullet* getBullet() override {
            return nullptr;
        }

        bool fireBullet() override {
            return false;
        }

        bool isUnderWater(const std::vector<std::pair<int, int>>& waterTileCoords) override {
            return false;
        }
        bool isUndestructibleBlock() override {
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
        bool isMovableBlock() override {
            return true;
        }
        virtual bool killPlayerTile(int playerPosX, int playerPosY) override {
            return false;
        }
        bool isWater() override {
            return false;
        }
    };