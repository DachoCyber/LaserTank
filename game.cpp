#include "include/game.h"
#include "include/playerInteraction.h"


MainGame::MainGame(int windowSizeX, int windowSizeY, int level) :
    window(std::make_unique<sf::RenderWindow>(
        sf::VideoMode(windowSizeX, windowSizeY), 
        "Laser Tank", 
        sf::Style::Close)),
    tileMap(level),
    player(tileMap.getPlayerPositionX(), tileMap.getPlayerPositionY(), windowSizeX, windowSizeY),
    windowSizeX(windowSizeX),
    windowSizeY(windowSizeY),
    bullet(nullptr)
{   
        int playerPosX = tileMap.getPlayerPositionX();
        int playerPosY = tileMap.getPlayerPositionY();
        sf::Vector2i playerPos = sf::Vector2i(playerPosX, playerPosY);
        player.setGridPosition(playerPos);
        window->setFramerateLimit(60);
        loadGoblet();
        loadGameOverFont(); 
       

}


void MainGame::run() {
    while (window->isOpen()) {
        if (!gameEnd()) {
    
            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window->close();
                if (event.type == sf::Event::KeyPressed && (!bulletFired || tileMap.getTileMap()[player.getGridPosition().y][player.getGridPosition().x] -> isTransportTrack()))
                    handleInput();
            }

            tileMap.updateTransportTracks();

            if(tileMap.getTileMap()[player.getGridPosition().y][player.getGridPosition().x] -> isTransportTrack() && !returnFromTrack) {
                if(returnFromTrack == false) {
                    std::cout << "false";
                } else {
                    std::cout << "true";
                }
                handlTransportableTrack(player.getGridPosition().y, player.getGridPosition().x);
                
            } 
            if(!tileMap.getTileMap()[player.getGridPosition().y][player.getGridPosition().x] -> isTransportTrack()) {
                returnFromTrack = false;
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
                } else if(gameLost()){
                    window -> draw(gameOverText);
                }
                window->display();
            }
        }
    }
}
bool MainGame :: playerKilledByEnemy() {
    return (static_cast<int>(bullet -> getPosition().x/tileSize == player.getGridPosition().x) && static_cast<int>(bullet -> getPosition().y/tileSize == player.getGridPosition().y));
}

bool MainGame :: shouldEnemyFireBullet() {
    for (int i = 0; i < tileMap.getTileMap().size(); i++) {
        for (int j = 0; j < tileMap.getTileMap()[i].size(); j++) {
            if (tileMap.getTileMap()[i][j]) {
                
                if(tileMap.getTileMap()[i][j]->killPlayer(
                    tileMap.getTileMap(),
                    player.getGridPosition().x * tileSize,
                    player.getGridPosition().y * tileSize)) {
            
                    tileMap.getTileMap()[i][j]->fireBullet();
                    bullet = tileMap.getTileMap()[i][j]->getBullet(); // Store bullet pointer for updates
                    bulletFired = true;
                    return true;
                }
            }
        }
    }
    return false;
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
    if (!bullet && shouldEnemyFireBullet()) {
        
    }
    if (bullet != nullptr) {
        const sf::Time updateInterval = sf::seconds(1.f/60.f);
        bullet->update(updateInterval);

        sf::Vector2f bulletPos = bullet->getPosition();
        if (static_cast<int>(bulletPos.x) / tileSize == player.getGridPosition().x &&
            static_cast<int>(bulletPos.y) / tileSize == player.getGridPosition().y) {
            killPlayer = true;
            bullet = nullptr;
        }
    }
}


void MainGame::render() {
    window->clear(sf::Color::White);
    window->draw(tileMap);
    window->draw(player);
    if(bullet != nullptr) {
        window -> draw(*bullet);
    }
    if(gameLost()) {
        window -> draw(gameOverText);
    }
    
    window->display();
}

bool  MainGame :: gameLost() {
    return player.getShouldKillPlayer() == true || killPlayer;
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
void MainGame::loadGameOverFont() {
    try {
        if (!weirdFont.loadFromFile("Fonts/Creepster-Regular.ttf")) {
            throw std::runtime_error("Cannot load weird font");
        }

        gameOverText.setFont(weirdFont);
    
        gameOverText.setString("GAME OVER");
    
        gameOverText.setCharacterSize(80);
    
        gameOverText.setFillColor(sf::Color::Red);
    
        gameOverText.setStyle(sf::Text::Bold | sf::Text::Italic);
    
        sf::FloatRect textBounds = gameOverText.getLocalBounds();
    
        gameOverText.setOrigin(textBounds.left + textBounds.width / 2.f,
                               textBounds.top + textBounds.height / 2.f);
                            
        gameOverText.setPosition(static_cast<float>(windowSizeX) / 2,
                                 static_cast<float>(windowSizeY) / 2);
    
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}


void MainGame :: handlTransportableTrack(int y, int x) {
    if(returnFromTrack) return;
    player.setDir(LEFT);
    if(player.validMove(x - 1, y)) {

            if(tileMap.getTileMap()[y][x-1] -> isTileMovableBlock() || 
                tileMap.getTileMap()[y][x-1] -> isBulletDestroyable() ||
                tileMap.getTileMap()[y][x-1] -> isMirror1() ||
                tileMap.getTileMap()[y][x-1] -> isMirror2() ||
                tileMap.getTileMap()[y][x-1] -> isMirror3() ||
                tileMap.getTileMap()[y][x-1] -> isMirror4() ||
                tileMap.getTileMap()[y][x-1] -> isTank()) {
                    returnFromTrack = true;
                    return;
            }
            int currGridCoordX = x;
            int currGridCoordY = y;

            returnFromTrack = false;
            std::cout << player.getGridPosition().x << std::endl;
            player.setGridPosition(sf::Vector2i(x - 1, y));
            std::cout << player.getGridPosition().x << std::endl;
        }
}