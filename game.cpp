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
    playerPosY(playerPosY),
    bullet(nullptr)
{   
        player.setGridPosition(sf::Vector2i(playerPosX, playerPosY));
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
                if (event.type == sf::Event::KeyPressed && !bulletFired)
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
        std::cout << "here" << std::endl;
        gameOverText.setString("GAME OVER");
        std::cout << "here" << std::endl;
        gameOverText.setCharacterSize(80);
        std::cout << "here" << std::endl;
        gameOverText.setFillColor(sf::Color::Red);
        std::cout << "here" << std::endl;
        gameOverText.setStyle(sf::Text::Bold | sf::Text::Italic);
        std::cout << "here" << std::endl;
        sf::FloatRect textBounds = gameOverText.getLocalBounds();
        std::cout << "here" << std::endl;
        gameOverText.setOrigin(textBounds.left + textBounds.width / 2.f,
                               textBounds.top + textBounds.height / 2.f);
                               std::cout << "here" << std::endl;
        gameOverText.setPosition(static_cast<float>(windowSizeX) / 2,
                                 static_cast<float>(windowSizeY) / 2);
        std::cout << "here" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
