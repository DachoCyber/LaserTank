#include "include/player.h"


Tank::Tank(int gridPosX, int gridPosY, int windowSizeX, int windowSizeY) 
    :
    dir(RIGHT),
    windowSizeX(windowSizeX),
    windowSizeY(windowSizeY)
{
    tankImg.loadFromFile("Images/tank.png");
    texture.loadFromImage(tankImg);
    sprite.setTexture(texture);
    sprite.setScale(sf::Vector2f(0.65, 0.65));  
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    setDir(dir);
    sprite.setPosition(sf::Vector2f(static_cast<float>(gridPosX * tileSize + tileSize/2), static_cast<float>(gridPosY*tileSize + tileSize/2)));
    updateSpritePosition();
    
    std::cout << sprite.getLocalBounds().width << " " << sprite.getLocalBounds().height << std::endl;
}



bool Tank::bulletInScreen() const {
    if (bullet && bullet->getPosition().x <= windowSizeX &&
        bullet->getPosition().x >= 0 &&
        bullet->getPosition().y <= windowSizeY &&
        bullet->getPosition().y >= 0) {
        return true;
    } else {
        return false;
    }
}


void Tank::setDir(Direction d) {
    dir = d;
    switch (dir) {
        case UP:    sprite.setRotation(0.f); break;
        case RIGHT: sprite.setRotation(90.f); break;
        case DOWN:  sprite.setRotation(180.f); break;
        case LEFT:  sprite.setRotation(270.f); break;
    }
}

Direction Tank::getDir() const {
    return dir;
}

sf::Vector2i Tank::getGridPosition() const {
    return gridPos;
}
/*
void Tank::handleInput() {
    if (moveQueued) return; // Only allow one move per key press

    sf::Vector2i newGridPos = gridPos;

    // UP
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if (!upPressed) {
            upPressed = true;
            if (dir != UP) {
                setDir(UP);
            } else {
                newGridPos.y -= 1;
                if (validMove(newGridPos.x, newGridPos.y)) {
                    gridPos = newGridPos;
                }
            }
        }
    } else {
        upPressed = false;
    }

    // DOWN
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if (!downPressed) {
            downPressed = true;
            if (dir != DOWN) {
                setDir(DOWN);
            } else {
                newGridPos.y += 1;
                if (validMove(newGridPos.x, newGridPos.y)) {
                    gridPos = newGridPos;
                }
            }
        }
    } else {
        downPressed = false;
    }

    // LEFT
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (!leftPressed) {
            leftPressed = true;
            if (dir != LEFT) {
                setDir(LEFT);
            } else {
                newGridPos.x -= 1;
                if (validMove(newGridPos.x, newGridPos.y)) {
                    gridPos = newGridPos;
                }
            }
        }
    } else {
        leftPressed = false;
    }

    // RIGHT
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if (!rightPressed) {
            rightPressed = true;
            if (dir != RIGHT) {
                setDir(RIGHT);
            } else {
                newGridPos.x += 1;
                if (validMove(newGridPos.x, newGridPos.y)) {
                    gridPos = newGridPos;
                }
            }
        }
    } else {
        rightPressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        fireBullet();
    }
}

*/
void Tank :: setGridPosition(sf::Vector2i gridPos) {
    this -> gridPos = gridPos;
    updateSpritePosition();
}

void Tank::update(sf::Time accTime, sf::Time updateInterval) {
    sprite.setPosition(gridPos.x * tileSize + tileSize / 2, gridPos.y * tileSize + tileSize / 2);

    if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) {
        moveQueued = false;
    }
    if(accTime >= updateInterval && bullet) {

        bullet->update(updateInterval);
        accTime -= updateInterval;
    }
}

void Tank::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite);
    if (bullet && bulletInScreen()) {
        target.draw(*bullet);
    }
}

void Tank::updateSpritePosition() {
    sprite.setPosition(sf::Vector2f(static_cast<float>(gridPos.x*tileSize + tileSize/2), static_cast<float>(gridPos.y*tileSize + tileSize/2)));
}

bool Tank :: validMove(int gridPosX, int gridPosy) const {
    return gridPosX >= 0 && gridPosX <= 19 && gridPosy >= 0 && gridPosy <= 19;
}
void Tank::fireBullet() {

    sf::Vector2f tankPos = sprite.getPosition();
    auto tankSize = tankImg.getSize();
    switch (dir) {
        case UP: bullet = new Bullet(sf::Vector2f(tankPos.x -2.f, tankPos.y - tileSize / 2 + 11.f), dir); break;
        case DOWN: bullet = new Bullet(sf::Vector2f(tankPos.x - 2.f, tankPos.y + tileSize / 2 - 11.f), dir); break;
        case RIGHT: bullet = new Bullet(sf::Vector2f(tankPos.x + tileSize / 2 -11.f, tankPos.y - 2.f), dir); break;
        case LEFT: bullet = new Bullet(sf::Vector2f(tankPos.x - tileSize / 2 +11.f, tankPos.y -1.f), dir); break;
    }

}

void Tank::deleteBullet() {
    if(bullet) {

        bullet = nullptr;
    }
}
