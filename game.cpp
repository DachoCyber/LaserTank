#include "include/game.h"

MainGame::MainGame(int windowSizeX, int windowSizeY) :
    window(std::make_unique<sf::RenderWindow>(
        sf::VideoMode(windowSizeX, windowSizeY), 
        "Laser Tank", 
        sf::Style::Close)),
    player(3, 3, windowSizeX, windowSizeY),
    tileMap(),
    windowSizeX(windowSizeX),
    windowSizeY(windowSizeY)
{
        window->setFramerateLimit(60);
}

void MainGame::run() {
    while(window->isOpen()) {
        sf::Event event;
        while(window->pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window->close();
        }

        timeSinceLastUpdate += gameClock.restart();
        
        // Fixed timestep updates
        while(timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;
            handleInput();
            update();
        }

        render();
    }
}

void MainGame::handleInput() {
    if(moveQueued) return;

    sf::Vector2i newGridPos = player.getGridPosition();
    bool moved = false;

    // UP
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if(!upPressed && player.getBullet() == nullptr) {
            upPressed = true;
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
    } else {
        upPressed = false;
    }

    // DOWN
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if(!downPressed && player.getBullet() == nullptr) {
            downPressed = true;
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
    } else {
        downPressed = false;
    }

    // LEFT
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player.getBullet() == nullptr) {
        if(!leftPressed) {
            leftPressed = true;
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
    } else {
        leftPressed = false;
    }

    // RIGHT
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if(!rightPressed && player.getBullet() == nullptr) {
            rightPressed = true;
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
    } else {
        rightPressed = false;
    }

    if(moved && validMove(newGridPos.x, newGridPos.y)) {
        player.setGridPosition(newGridPos);
        moveQueued = true;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player.getBullet() == nullptr) {
        int x = player.getGridPosition().x;
        int y = player.getGridPosition().y;
        bool fireBullet = true;
        if(tileMap.getTileMap()[y/2][x/2] -> isWalkable()) {
            std::cout << "current player position is walkable!" <<std::endl;
        }
        if(tileMap.getTileMap()[y/2][x/2] -> isBulletDestroyable()) {
            std::cout << "current player position is bullet destroyable!" << std::endl;
        }
        

        // Check adjacent tile in the direction player is facing
        switch(player.getDir()) {
            case UP:

                if(y - 1 >= 0 && tileMap.getTileMap()[y/2 - 1][x/2]->isBulletDestroyable()) {
                    tileMap.destroyTile(x, y - 1);
                    std::cout << "bullet not fired!" << std::endl;
                    fireBullet = false;
                }
                break;
            case DOWN:
                if(y + 1 < tileMap.getTileMap().size() && tileMap.getTileMap()[y/2 + 1][x/2]->isBulletDestroyable()) {
                    tileMap.destroyTile(x, y + 1);
                    fireBullet = false;
                }
                break;
            case LEFT:
                if(x - 1 >= 0 && tileMap.getTileMap()[y/2][x/2 - 1]->isBulletDestroyable()) {
                    tileMap.destroyTile(x - 1, y);
                    fireBullet = false;
                }
                break;
            case RIGHT:
                if(x + 1 < tileMap.getTileMap()[y].size() && tileMap.getTileMap()[y/2][x/2 + 1]->isBulletDestroyable()) {
                    tileMap.destroyTile(x + 1, y);
                    fireBullet = false;
                }
                break;
        }
        
        // Only fire bullet if there wasn't a destructible block adjacent
        if(fireBullet) {
            player.fireBullet();
        }
    }
}

void MainGame::update() {
    // Reset move queue if no keys pressed
    if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
         sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
         sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
         sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) {
        moveQueued = false;
    }

    // game.h -> (map.h, player.h), bulletInteraction.h -> (player.h, map.h), game.h -> bulletInteraction.h

    // Update bullet if exists
    if(player.getBullet() != nullptr) {

        BulletInteraction *bulletInteract = new BulletInteraction(windowSizeX, windowSizeY, player, tileMap);
        bulletInteract -> interact();
        delete bulletInteract;
    } else {
        spacePressed = false;
    }
}


void MainGame::render() {
    window->clear(sf::Color::White);
    window->draw(tileMap);
    window->draw(player);
    window->display();
}

bool MainGame::validMove(int x, int y) const {
    return x >= 0 && x < 18  && 
           y >= 0 && y < 18;
}
