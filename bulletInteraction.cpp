#include "include/bulletInteraction.h"

BulletInteraction::BulletInteraction(int windowSizeX, int windowSizeY, Tank& tank, Map& map)
    : windowSizeX(windowSizeX), windowSizeY(windowSizeY), player(tank), tileMap(map) {}

void BulletInteraction :: interact() {

    if(player.getBullet() == nullptr) {
        return;
    }
    

    player.getBullet()->update(timePerFrame);
    
    if(player.getBullet()->getPosition().x >= windowSizeX || player.getBullet()->getPosition().x < 0 ||
        player.getBullet()->getPosition().y >= windowSizeY || player.getBullet()->getPosition().y < 0) {
            
        player.deleteBullet();
        return;
    }

    int bulletGridPosX = player.getBullet()->getPosition().x/tileSize;
    int bulletGridPosY = player.getBullet()->getPosition().y/tileSize;
    std::cout << bulletGridPosX << " " << bulletGridPosY << std::endl;

    if (bulletGridPosX >= 0 && bulletGridPosX < tileMap.getTileMap()[0].size() &&
    bulletGridPosY >= 0 && bulletGridPosY < tileMap.getTileMap().size()) {
    
        if (tileMap.getTileMap()[bulletGridPosY][bulletGridPosX] &&
            tileMap.getTileMap()[bulletGridPosY][bulletGridPosX]->isBulletDestroyable()) {

            player.deleteBullet();
            tileMap.destroyTile(bulletGridPosX, bulletGridPosY);
            }
        }
    
} 