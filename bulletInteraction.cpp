#include "include/bulletInteraction.h"

BulletInteraction::BulletInteraction(int windowSizeX, int windowSizeY, Tank& tank, Map& map)
    : windowSizeX(windowSizeX), windowSizeY(windowSizeY), player(tank), tileMap(map) {}

void BulletInteraction :: interact() {

    if(player.getBullet() == nullptr) {
        return;
    }

    /*if(abs(player.getBullet() -> getPosition().x/tileSize - player.getGridPosition().x) == 0
      && abs(player.getBullet() -> getPosition().y/tileSize - player.getGridPosition().y) == 0) {
        player.getBullet() -> setTransparentColor();
    } else {
        player.getBullet() -> returnOldColor();
    }*/
    
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
        if(tileMap.getTileMap()[bulletGridPosY][bulletGridPosX] -> isUndestructibleBlock()) {
            player.deleteBullet();
        }
        if(tileMap.getTileMap()[bulletGridPosY][bulletGridPosX] -> isTileMovableBlock()) {
            
            if(player.getBullet() -> dir == UP) {
                if(bulletGridPosY > 0 && (player.getGridPosition().x != bulletGridPosX || player.getGridPosition().y != bulletGridPosY - 1)) {
                    if(tileMap.getTileMap()[bulletGridPosY - 1][bulletGridPosX] -> isOverlappled()) {
                        tileMap.moveTile(bulletGridPosY - 1, bulletGridPosX, bulletGridPosY, bulletGridPosX);
                    }
                }
            } else if(player.getBullet() -> dir == DOWN) {
                if(bulletGridPosY < tileMap.getTileMap().size() - 1 && (player.getGridPosition().x != bulletGridPosX || player.getGridPosition().y != bulletGridPosY + 1)) {
                    if(tileMap.getTileMap()[bulletGridPosY + 1][bulletGridPosX] -> isOverlappled()) {

                        tileMap.moveTile(bulletGridPosY + 1, bulletGridPosX, bulletGridPosY, bulletGridPosX);
                    }
                }
            }else if(player.getBullet() -> dir == LEFT) {
                if(bulletGridPosX > 0 && (player.getGridPosition().x != bulletGridPosX - 1 || player.getGridPosition().y != bulletGridPosY)) {
                    if(tileMap.getTileMap()[bulletGridPosY][bulletGridPosX - 1] -> isOverlappled()) {

                        tileMap.moveTile(bulletGridPosY, bulletGridPosX - 1, bulletGridPosY, bulletGridPosX);
                    }
                }
            } else if(player.getBullet() -> dir == RIGHT) {
                if(bulletGridPosX < tileMap.getTileMap()[bulletGridPosY].size() && (player.getGridPosition().x != bulletGridPosX + 1 || player.getGridPosition().y != bulletGridPosY)) {
                    if(tileMap.getTileMap()[bulletGridPosY][bulletGridPosX + 1] -> isOverlappled()) {

                        tileMap.moveTile(bulletGridPosY, bulletGridPosX + 1, bulletGridPosY, bulletGridPosX);
                    }
                }
            }
            player.deleteBullet();
            return;
        }
        if(tileMap.getTileMap()[bulletGridPosY][bulletGridPosX]
    && tileMap.getTileMap()[bulletGridPosY][bulletGridPosX]->isMirror1()) 
{   
    std::cout << lastBulletGridPosX << " " << lastBulletGridPosY << " " << bulletGridPosX << " "<< bulletGridPosY << std::endl;
    // First ensure bullet is actually on the mirror tile
    //if(!(bulletGridPosX == lastBulletGridPosX && bulletGridPosY == lastBulletGridPosY))
    //{
        // Hit from left - reflect down
        
        if(lastBulletGridPosX < bulletGridPosX && (lastBulletGridPosY == bulletGridPosY)) {

            player.getBullet()->changeVelocity(DOWN, 2);
            player.getBullet() -> dir = DOWN;
        }
        // Hit from right - move mirror left
        else if(lastBulletGridPosX > bulletGridPosX || (player.getGridPosition().x - bulletGridPosX == 1 && player.getGridPosition().y == bulletGridPosY)) {
            if(bulletGridPosX > 0) {  // Can we move left?
                bool canMove = (player.getGridPosition().x != bulletGridPosX - 1 || player.getGridPosition().y != bulletGridPosY)
                               && bulletGridPosX > 0 && !tileMap.getTileMap()[bulletGridPosY][bulletGridPosX - 1] || 
                               tileMap.getTileMap()[bulletGridPosY][bulletGridPosX - 1]->isOverlappled();
                
                if(canMove) {
                    tileMap.moveTile(bulletGridPosY, bulletGridPosX - 1,
                                   bulletGridPosY, bulletGridPosX);
                }
            }
            player.deleteBullet();
        }
        // Hit from bottom - reflect left
        else if(lastBulletGridPosY > bulletGridPosY || (player.getGridPosition().y - bulletGridPosY == 1 && player.getGridPosition().x == bulletGridPosX)) {
            player.getBullet()->changeVelocity(LEFT, 2);
            player.getBullet() -> dir = LEFT;
        }
        // Hit from top - move mirror down
        else if(lastBulletGridPosY < bulletGridPosY) {
            if(bulletGridPosY < tileMap.getTileMap().size() - 1) {  // Can we move down?
                bool canMove = (player.getGridPosition().x != bulletGridPosX  || player.getGridPosition().y != bulletGridPosY + 1) &&
                               bulletGridPosY < 17 && (!tileMap.getTileMap()[bulletGridPosY + 1][bulletGridPosX] || 
                               tileMap.getTileMap()[bulletGridPosY + 1][bulletGridPosX]->isOverlappled());
                std::cout << "1" << std::endl;
                if(player.getGridPosition().x != bulletGridPosX  && player.getGridPosition().y != bulletGridPosY + 1) {
                    std::cout << "3" << std::endl;
                }
                if(canMove) {
                    std::cout << "2" << std::endl;
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
        
        if(lastBulletGridPosX > bulletGridPosX || (player.getGridPosition().x - bulletGridPosX == 1 && player.getGridPosition().y == bulletGridPosY)) {
            player.getBullet()->changeVelocity(DOWN, 1);
            player.getBullet() -> dir = DOWN;
            std::cout << "now it should turn down!" << lastBulletGridPosX << " " <<  bulletGridPosX << " " << player.getGridPosition().x << " " << bulletGridPosX << std::endl;
        }
        // Hit from right - move mirror left
        else if(lastBulletGridPosX < bulletGridPosX || -player.getGridPosition().x + bulletGridPosX == 1) {
            if(bulletGridPosX > 0) {  // Can we move left?
                bool canMove = (player.getGridPosition().x != bulletGridPosX + 1 || player.getGridPosition().y != bulletGridPosY) &&
                                bulletGridPosX > 0 && !tileMap.getTileMap()[bulletGridPosY][bulletGridPosX + 1] || 
                             tileMap.getTileMap()[bulletGridPosY][bulletGridPosX + 1]->isOverlappled();
                
                if(canMove && tileMap.getTileMap()[bulletGridPosY][bulletGridPosX + 1]->isOverlappled()) {
                    tileMap.moveTile(bulletGridPosY, bulletGridPosX + 1,
                                   bulletGridPosY, bulletGridPosX);
                }
            }
            player.deleteBullet();
        }
        // Hit from bottom - reflect left
        else if(lastBulletGridPosY > bulletGridPosY  || (player.getGridPosition().y - bulletGridPosY == 1 && player.getGridPosition().x == bulletGridPosX)) {
            std::cout << "now it should turn right!" << std::endl;
            player.getBullet()->changeVelocity(RIGHT, 1);
            player.getBullet() -> dir = RIGHT;
        }
        // Hit from top - move mirror down
        else if(lastBulletGridPosY < bulletGridPosY ) {
            if(bulletGridPosY < tileMap.getTileMap().size() - 1) {  // Can we move down?
                bool canMove = (player.getGridPosition().x != bulletGridPosX || player.getGridPosition().y != bulletGridPosY + 1) &&
                             bulletGridPosY < 17 && (!tileMap.getTileMap()[bulletGridPosY + 1][bulletGridPosX] || 
                             tileMap.getTileMap()[bulletGridPosY + 1][bulletGridPosX]->isOverlappled());
                
                if(canMove) {
                    tileMap.moveTile(bulletGridPosY + 1, bulletGridPosX,
                                   bulletGridPosY, bulletGridPosX);
                }
            }
            player.deleteBullet();
        }
    }
    if(tileMap.getTileMap()[bulletGridPosY][bulletGridPosX]
    && tileMap.getTileMap()[bulletGridPosY][bulletGridPosX]->isMirror3()) 
{   
    std::cout << lastBulletGridPosX << " " << lastBulletGridPosY << " " << bulletGridPosX << " "<< bulletGridPosY << std::endl;
    // First ensure bullet is actually on the mirror tile
    //if(!(bulletGridPosX == lastBulletGridPosX && bulletGridPosY == lastBulletGridPosY))
    //{
        // Hit from left - reflect down
        if(lastBulletGridPosX < bulletGridPosX || (-player.getGridPosition().x + bulletGridPosX == 1 && player.getGridPosition().y == bulletGridPosY)) {
            player.getBullet()->changeVelocity(UP, 3);
            player.getBullet() -> dir = UP;
        }
        // Hit from right - move mirror left
        else if(lastBulletGridPosX > bulletGridPosX || player.getGridPosition().x - bulletGridPosX == 1) {
            if(bulletGridPosX > 0) {  // Can we move left?
                bool canMove = (player.getGridPosition().x != bulletGridPosX - 1 || player.getGridPosition().y != bulletGridPosY)
                              && bulletGridPosX > 0 && !tileMap.getTileMap()[bulletGridPosY][bulletGridPosX - 1] || 
                             tileMap.getTileMap()[bulletGridPosY][bulletGridPosX - 1]->isOverlappled();
                
                if(canMove) {
                    tileMap.moveTile(bulletGridPosY, bulletGridPosX - 1,
                                   bulletGridPosY, bulletGridPosX);
                }
            }
            player.deleteBullet();
        }
        // Hit from bottom - reflect left
        else if(lastBulletGridPosY < bulletGridPosY || (-player.getGridPosition().y + bulletGridPosY == 1 && player.getGridPosition().x == bulletGridPosX)) {
            player.getBullet()->changeVelocity(LEFT, 3);
            player.getBullet() -> dir = LEFT;
        }
        // Hit from top - move mirror down
        else if(lastBulletGridPosY > bulletGridPosY || player.getGridPosition().y - bulletGridPosY == 1) {
            if(bulletGridPosY > 0) {  // Can we move down?
                bool canMove = (player.getGridPosition().x != bulletGridPosX || player.getGridPosition().y != bulletGridPosY - 1) &&
                             bulletGridPosY > 0 && (!tileMap.getTileMap()[bulletGridPosY - 1][bulletGridPosX] || 
                             tileMap.getTileMap()[bulletGridPosY - 1][bulletGridPosX]->isOverlappled());
                
                if(canMove) {
                    tileMap.moveTile(bulletGridPosY - 1, bulletGridPosX,
                                   bulletGridPosY, bulletGridPosX);
                }
            }
            player.deleteBullet();
        }
    }
    if(tileMap.getTileMap()[bulletGridPosY][bulletGridPosX]
    && tileMap.getTileMap()[bulletGridPosY][bulletGridPosX]->isMirror4()) 
{   
    std::cout << lastBulletGridPosX << " " << lastBulletGridPosY << " " << bulletGridPosX << " "<< bulletGridPosY << std::endl;
    // First ensure bullet is actually on the mirror tile
    //if(!(bulletGridPosX == lastBulletGridPosX && bulletGridPosY == lastBulletGridPosY))
    //{
        // Hit from left - reflect down
        if(lastBulletGridPosX > bulletGridPosX || (player.getGridPosition().x - bulletGridPosX == 1 && player.getGridPosition().y == bulletGridPosY)) {
            std::cout << static_cast<int>(player.getBullet() -> getPosition().x/tileSize) << "    " << bulletGridPosX << std::endl;
            player.getBullet()->changeVelocity(UP, 3);
            player.getBullet() -> dir = UP;
        }
        // Hit from right - move mirror left
        else if(lastBulletGridPosX < bulletGridPosX || (player.getGridPosition().x - bulletGridPosX == -1 && player.getGridPosition().y == bulletGridPosY)) {
            if(bulletGridPosX < tileMap.getTileMap()[bulletGridPosY].size()) {  // Can we move left?
                bool canMove = (player.getGridPosition().x != bulletGridPosX + 1 || player.getGridPosition().y != bulletGridPosY)
                             && bulletGridPosX > 0 && !tileMap.getTileMap()[bulletGridPosY][bulletGridPosX + 1] || 
                             tileMap.getTileMap()[bulletGridPosY][bulletGridPosX + 1]->isOverlappled();
                
                if(canMove) {
                    tileMap.moveTile(bulletGridPosY, bulletGridPosX + 1,
                                   bulletGridPosY, bulletGridPosX);
                }
            }
            player.deleteBullet();
        }
        // Hit from bottom - reflect left
        else if(lastBulletGridPosY < bulletGridPosY || (player.getGridPosition().y - bulletGridPosY == -1 && player.getGridPosition().x == bulletGridPosX)) {
            player.getBullet()->changeVelocity(RIGHT, 3);
            player.getBullet() -> dir = RIGHT;
        }
        // Hit from top - move mirror down
        else if(lastBulletGridPosY > bulletGridPosY) {
            if(bulletGridPosY > 0) {  // Can we move down?
                bool canMove = (player.getGridPosition().x != bulletGridPosX || player.getGridPosition().y != bulletGridPosY - 1)
                            && bulletGridPosY > 0 && (!tileMap.getTileMap()[bulletGridPosY - 1][bulletGridPosX] || 
                             tileMap.getTileMap()[bulletGridPosY - 1][bulletGridPosX]->isOverlappled());
                
                if(canMove) {
                    tileMap.moveTile(bulletGridPosY - 1, bulletGridPosX,
                                   bulletGridPosY, bulletGridPosX);
                }
            }
            player.deleteBullet();
        }
    }
}

     