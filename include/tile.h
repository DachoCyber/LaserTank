#pragma once

#include <SFML/Graphics.hpp>
#include <string>


extern sf::Texture walkableTexture;
extern sf::Texture destructibleTexture;


enum TileType {
    WALKABLE_GROUND,
    DESTRUCTIBLE_BLOCK
};

class Tile : public sf::Drawable {

protected:
    const int tileSize = 32;
    int posX, posY;

    sf::Texture tex;
    sf::Sprite sprite;

    bool walkable;
public:
 
    Tile(int x, int y) {
        posX = x;
        posY = y;
    }
    virtual bool isWalkable() = 0;
    virtual bool isBulletDestroyable() = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates) const override {
        target.draw(sprite);
    }
    Tile() : walkable(false), posX(0), posY(0) {}
};