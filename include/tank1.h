    #pragma once

    #include "tile.h"
    #include "bullet.h"

    #include <memory>

    class EnemyTank1 : public Tile {
    public:
        int dir;
        EnemyTank1(int x, int y, int dir) : Tile(x, y) {
            try {
                this-> dir = dir;
                walkable = false;
                switch(dir) {
                    case 0 :
                        if(!tex.loadFromFile("/home/dalibor/Desktop/LaserTank/Images/tank1.png")) {
                        throw new std::runtime_error("Cannot open image walkableGround.png!");
                        }
                        break;
                    default :
                        if(!tex.loadFromFile("/home/dalibor/Desktop/LaserTank/Images/tank2.png")) {
                            throw new std::runtime_error("Cannot open image walkableGround.png!");
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
            std::cout << playerPosX << " " << playerPosY << std::endl;
            switch(dir) {
                case 0:
                    
                    if(playerPosY != posY) return false;
                    std::cout << "defe" << std::endl;
                    if(posX < playerPosX) return false;
                    for(int j = posX/tileSize - 1; j > playerPosX/tileSize; j--) {
                        int gPosY = posY/tileSize;
    

                        if(!(tileMap[gPosY][j]->isWalkable() || tileMap[gPosY][j]->isWater())) {
                                return false;
                            }
                    }
                    
                    break;
                case 1:
                    if(playerPosY != posY) return false;
                    if(posX > playerPosX) return false;
                    for(int j = posX/tileSize + 1; j < playerPosX/tileSize; j++) {
                        int gPosY = posY/tileSize;
                

                        if(!(tileMap[gPosY][j]->isWalkable() || tileMap[gPosY][j]->isWater())) {
                                return false;
                            }
                    }
                    break;
            }

            
            return true;
        }

        Bullet* bullet;
        bool fireBullet() override {
            if(dir == 0) {

                bullet = new Bullet(sf::Vector2f(posX, posY + tileSize/2), LEFT, true);
            } else {
                bullet = new Bullet(sf::Vector2f(posX, posY + tileSize/2), RIGHT, true);
            }
            return true;
        }

        Bullet* getBullet() override {
            return bullet;
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
        virtual bool killPlayerTile(int playerPosX, int playerPosY) override {
            return false;
        }
        bool isWater() override {
            return false;
        }
    };