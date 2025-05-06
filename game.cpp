#include "include/game.h"

MainGame::MainGame(int windowSizeX, int windowSizeY) :
    window(std::make_unique<sf::RenderWindow>(
        sf::VideoMode(windowSizeX, windowSizeY), 
        "Laser Tank", 
        sf::Style::Close)),
    player(3, 3, windowSizeX, windowSizeY),
    tileMap(),
    windowSizeX(windowSizeX),
    windowSizeY(windowSizeY),
    countSpacePressed(0)
{   
        window->setFramerateLimit(60);
}

void MainGame::run() {
    while(window->isOpen()) {
        sf::Event event;
        while(window->pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window->close();
            if(event.type == sf::Event::KeyPressed)
                handleInput();
        }

    
        update();

        render();
    }
}

void MainGame::handleInput() {


    sf::Vector2i newGridPos = player.getGridPosition();
    bool moved = false;

    // UP
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player.getBullet() == nullptr) {
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player.getBullet() == nullptr) {
        
        if(!player.deleteAdjBlockIfExists(tileMap)) {
            player.fireBullet();
        }
    }

    if(moved && validMove(newGridPos.x, newGridPos.y)) {
        player.setGridPosition(newGridPos);
        moveQueued = true;
    }
}

void MainGame::update() {

    // game.h -> (map.h, player.h), bulletInteraction.h -> (player.h, map.h), game.h -> bulletInteraction.h

    // Update bullet if exists
    if(player.getBullet() != nullptr) {

        BulletInteraction *bulletInteract = new BulletInteraction(windowSizeX, windowSizeY, player, tileMap);
        bulletInteract -> interact();
        delete bulletInteract;
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
