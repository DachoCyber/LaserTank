#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "tile.h"
#include "walkableGround.h"

class Map : public sf::Drawable {
public:
    Map();
    virtual ~Map() = default;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override ;
    bool isWalkable(int x, int y) const;
    sf::Vector2f getTilePosition(int x, int y) const;
    int getTileSize() const { return tileSize; }
    const std::vector<std::vector<std::unique_ptr<Tile>>>& getTileMap() const {return tiles;}
    const std::vector<std::vector<int>> getTileMapInt() const {return tileMap;}
    void destroyTile(int gridPosX, int gridPosY) {
        std::unique_ptr<Tile> tile = std::make_unique<WalkableGround>(gridPosX*tileSize, gridPosY*tileSize);
        tiles[gridPosY][gridPosX] = std::move(tile);
    }

private:
    void loadTextures();
    void buildMap();

    const int tileSize = 32;
    const int mapWidth = 19;
    const int mapHeight = 19;
    
    std::vector<std::vector<int>> tileMap;
    std::vector<std::vector<sf::Sprite>> sprites;
    std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
    
    sf::Texture walkableTexture;
    sf::Texture destructibleTexture;
};