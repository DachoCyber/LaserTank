#include "include/game.h"
#include "include/playerInteraction.h"


MainGame::MainGame(int windowSizeX, int windowSizeY, int playerPosX, int playerPosY) :
    window(std::make_unique<sf::RenderWindow>(
        sf::VideoMode(windowSizeX, windowSizeY), 
        "Laser Tank", 
        sf::Style::Close)),
    player(3, 3, windowSizeX, windowSizeY),
    tileMap(),
    windowSizeX(windowSizeX),
    windowSizeY(windowSizeY),
    playerPosX(playerPosX),
    playerPosY(playerPosY)
{   
        player.setGridPosition(sf::Vector2i(playerPosX, playerPosY));
        window->setFramerateLimit(60);
        loadGoblet();
}void MainGame::run() {
    while (window->isOpen()) {
        if (!gameEnd()) {
            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window->close();
                if (event.type == sf::Event::KeyPressed)
                    handleInput();
            }

            update();
            render();
        } else {
            // Game over loop
            while (window->isOpen()) {
                sf::Event event;
                while (window->pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window->close();
                }

                window->clear(sf::Color::White);
                if (gameWon()) {
                    drawGoblet();
                }
                // Optionally show "You Won!" text
                window->display();
            }
        }
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

bool  MainGame :: gameLost() {
    return player.getShouldKillPlayer() == true;
}

bool MainGame :: gameWon() {
    return player.getGridPosition().x*tileSize == tileMap.getFlagCoordX() && player.getGridPosition().y*tileSize == tileMap.getFlagCoordY();
}

bool MainGame :: gameEnd() {
    return gameLost() || gameWon();
}

void MainGame::drawGoblet() {

    window->draw(gobletSprite);
}

void MainGame :: loadGoblet() {
    try {
        if (!gobletTexture.loadFromFile("/home/dalibor/Desktop/LaserTank/Images/goblet.png")) {
            throw std::runtime_error("Cannot load goblet image");
        }

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return;
    }
    gobletSprite.setTexture(gobletTexture);
    gobletSprite.setOrigin(gobletSprite.getLocalBounds().width / 2, gobletSprite.getLocalBounds().height / 2);
    gobletSprite.setPosition(sf::Vector2f(static_cast<float>(windowSizeX)/2, static_cast<float>(windowSizeY)/2));
}