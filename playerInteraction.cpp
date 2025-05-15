#include "include/playerInteraction.h"

bool validMove(int x, int y) {
    return x >= 0 && x < 16  && 
           y >= 0 && y < 16;
}

PlayerInteraction :: PlayerInteraction(int windowSizeX, int windowSizeY, Tank& player, Map& map, sf::Keyboard::Key key) :
        windowSizeX(windowSizeX),
        windowSizeY(windowSizeY),
        player(player),
        tileMap(map),
        pressedKey(key) 
{
    
}

void PlayerInteraction :: handleMovement() {
    sf::Vector2i newGridPos = player.getGridPosition();
    bool moved = false;

    // UP
    if(pressedKey == sf::Keyboard::Key::Up) {
        if(player.getBullet() == nullptr) {
            if(player.getDir() != UP) {
                player.setDir(UP);
            } else {
                if(validMove(newGridPos.x, newGridPos.y - 1)) {

                    if(tileMap.getTileMap()[newGridPos.y - 1][newGridPos.x] -> isWalkable()) {

                        newGridPos.y -= 1;
                        moved = true;
                    }
                }
            }
        }
    }

    // DOWN
    if(pressedKey == sf::Keyboard::Key::Down) {
        if(player.getBullet() == nullptr) {
            if(player.getDir() != DOWN) {
                player.setDir(DOWN);
            } else {
                if(validMove(newGridPos.x, newGridPos.y + 1)) {

                    if(tileMap.getTileMap()[newGridPos.y + 1][newGridPos.x] -> isWalkable()) {

                        newGridPos.y += 1;
                        moved = true;
                    }
                }
            }
        }
    }

    

    // LEFT
    if(pressedKey == sf::Keyboard::Key::Left && player.getBullet() == nullptr) {
        if(player.getDir() != LEFT) {
            player.setDir(LEFT);
        } else {
            if(validMove(newGridPos.x - 1, newGridPos.y)) {

                if(tileMap.getTileMap()[newGridPos.y][newGridPos.x - 1] -> isWalkable()) {

                    newGridPos.x -= 1;
                    moved = true;
                }
            }
        }
    }
    

    // RIGHT
    if(pressedKey == sf::Keyboard::Key::Right) {
        if(player.getBullet() == nullptr) {
            if(player.getDir() != RIGHT) {
                player.setDir(RIGHT);
            } else {
                if(validMove(newGridPos.y, newGridPos.x + 1)) {

                    if(tileMap.getTileMap()[newGridPos.y][newGridPos.x + 1] -> isWalkable()) {
                        newGridPos.x += 1;
                        moved = true;
                    }
                }
                
            }
        }
    }

    // SPACE
    if(pressedKey == sf::Keyboard::Key::Space && player.getBullet() == nullptr) {
        
        if(!player.deleteAdjBlockIfExists(tileMap)) {
            player.fireBullet();
        }
    }

    if(moved && validMove(newGridPos.x, newGridPos.y)) {
        player.setGridPosition(newGridPos);
        if(tileMap.getTileMap()[newGridPos.y][newGridPos.x] -> isWater()) {
            player.setShouldKillPlayer();
        }
    }
}