#include "include/bulletInteraction.h"

BulletInteraction::BulletInteraction(int windowSizeX, int windowSizeY, Tank& tank, Map& map)
    : windowSizeX(windowSizeX), windowSizeY(windowSizeY), player(tank), tileMap(map) {}

void BulletInteraction :: interact() {

    if(player.getBullet() == nullptr) {
        return;
    }
    
    int lastBulletGridPosX = player.getBullet()->getPosition().x/tileSize;
    int lastBulletGridPosY = player.getBullet()->getPosition().y/tileSize;

    player.getBullet()->update(timePerFrame);
    
    if(player.getBullet()->getPosition().x >= windowSizeX || player.getBullet()->getPosition().x < 0 ||
        player.getBullet()->getPosition().y >= windowSizeY || player.getBullet()->getPosition().y < 0) {
            
        player.deleteBullet();
        return;
    }

    int bulletGridPosX = player.getBullet()->getPosition().x/tileSize;
    int bulletGridPosY = player.getBullet()->getPosition().y/tileSize;
        //std::cout << bulletGridPosX << " " << bulletGridPosY << std::endl;



    if (bulletGridPosX >= 0 && bulletGridPosX < tileMap.getTileMap()[0].size() &&
    bulletGridPosY >= 0 && bulletGridPosY < tileMap.getTileMap().size()) {
    
        if (tileMap.getTileMap()[bulletGridPosY][bulletGridPosX] &&
            tileMap.getTileMap()[bulletGridPosY][bulletGridPosX]->isBulletDestroyable()) {

            player.deleteBullet();
            tileMap.destroyTile(bulletGridPosX, bulletGridPosY);
            }
        if(tileMap.getTileMap()[bulletGridPosY][bulletGridPosX]
    && tileMap.getTileMap()[bulletGridPosY][bulletGridPosX]->isMirror1()) 
{   
    std::cout << lastBulletGridPosX << " " << lastBulletGridPosY << " " << bulletGridPosX << " "<< bulletGridPosY << std::endl;
    // First ensure bullet is actually on the mirror tile
    //if(!(bulletGridPosX == lastBulletGridPosX && bulletGridPosY == lastBulletGridPosY))
    //{
        // Hit from left - reflect down
        if(lastBulletGridPosX < bulletGridPosX) {
            player.getBullet()->changeVelocity(DOWN, 1);
        }
        // Hit from right - move mirror left
        else if(lastBulletGridPosX > bulletGridPosX || player.getGridPosition().x > bulletGridPosX) {
            if(bulletGridPosX > 0) {  // Can we move left?
                bool canMove = bulletGridPosX > 0 && !tileMap.getTileMap()[bulletGridPosY][bulletGridPosX - 1] || 
                             tileMap.getTileMap()[bulletGridPosY][bulletGridPosX - 1]->isOverlappled();
                
                if(canMove) {
                    tileMap.moveTile(bulletGridPosY, bulletGridPosX - 1,
                                   bulletGridPosY, bulletGridPosX);
                }
            }
            player.deleteBullet();
        }
        // Hit from bottom - reflect left
        else if(lastBulletGridPosY > bulletGridPosY || player.getGridPosition().y > bulletGridPosY) {
            player.getBullet()->changeVelocity(LEFT, 1);
        }
        // Hit from top - move mirror down
        else if(lastBulletGridPosY < bulletGridPosY ) {
            if(bulletGridPosY < tileMap.getTileMap().size() - 1) {  // Can we move down?
                bool canMove = bulletGridPosY < 17 && (!tileMap.getTileMap()[bulletGridPosY + 1][bulletGridPosX] || 
                             tileMap.getTileMap()[bulletGridPosY + 1][bulletGridPosX]->isOverlappled());
                
                if(canMove) {
                    tileMap.moveTile(bulletGridPosY + 1, bulletGridPosX,
                                   bulletGridPosY, bulletGridPosX);
                }
            }
            player.deleteBullet();
        }
    }
}
if(tileMap.getTileMap()[bulletGridPosY][bulletGridPosX]
    && tileMap.getTileMap()[bulletGridPosY][bulletGridPosX]->isMirror2()) 
{   
    std::cout << lastBulletGridPosX << " " << lastBulletGridPosY << " " << bulletGridPosX << " "<< bulletGridPosY << std::endl;
    // First ensure bullet is actually on the mirror tile
    //if(!(bulletGridPosX == lastBulletGridPosX && bulletGridPosY == lastBulletGridPosY))
    //{
        // Hit from left - reflect down
        if(lastBulletGridPosX > bulletGridPosX || player.getGridPosition().x - bulletGridPosX == 1) {
            player.getBullet()->changeVelocity(DOWN, 1);
        }
        // Hit from right - move mirror left
        else if(lastBulletGridPosX < bulletGridPosX || player.getGridPosition().x < bulletGridPosX) {
            if(bulletGridPosX > 0) {  // Can we move left?
                bool canMove = bulletGridPosX > 0 && !tileMap.getTileMap()[bulletGridPosY][bulletGridPosX + 1] || 
                             tileMap.getTileMap()[bulletGridPosY][bulletGridPosX + 1]->isOverlappled();
                
                if(canMove && tileMap.getTileMap()[bulletGridPosY][bulletGridPosX + 1]->isOverlappled()) {
                    tileMap.moveTile(bulletGridPosY, bulletGridPosX + 1,
                                   bulletGridPosY, bulletGridPosX);
                }
            }
            player.deleteBullet();
        }
        // Hit from bottom - reflect left
        else if(lastBulletGridPosY > bulletGridPosY || player.getGridPosition().y > bulletGridPosY) {
            player.getBullet()->changeVelocity(RIGHT, 1);
        }
        // Hit from top - move mirror down
        else if(lastBulletGridPosY < bulletGridPosY ) {
            if(bulletGridPosY < tileMap.getTileMap().size() - 1) {  // Can we move down?
                bool canMove = bulletGridPosY < 17 && (!tileMap.getTileMap()[bulletGridPosY + 1][bulletGridPosX] || 
                             tileMap.getTileMap()[bulletGridPosY + 1][bulletGridPosX]->isOverlappled());
                
                if(canMove) {
                    tileMap.moveTile(bulletGridPosY + 1, bulletGridPosX,
                                   bulletGridPosY, bulletGridPosX);
                }
            }
            player.deleteBullet();
        }
    }
}

     