#include "include/game.h"
#include "include/playerInteraction.h"

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
    while(window->isOpen() && player.getShouldKillPlayer() == false) {
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
    sf::Keyboard::Key pressedKey = sf::Keyboard::Unknown;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        pressedKey = sf::Keyboard::Up;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        pressedKey = sf::Keyboard::Down;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        pressedKey = sf::Keyboard::Left;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        pressedKey = sf::Keyboard::Right;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        pressedKey = sf::Keyboard::Space;
    }

    if (pressedKey != sf::Keyboard::Unknown) {
        PlayerInteraction* playerInteraction = new PlayerInteraction(windowSizeX, windowSizeY, player, tileMap, pressedKey);
        playerInteraction -> handleMovement();
        delete playerInteraction;
    }
    sf::Vector2i newGridPos = player.getGridPosition();
    bool moved = false;

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
