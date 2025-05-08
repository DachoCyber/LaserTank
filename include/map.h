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
    void moveTile(int newGridPosY, int newGridPosX, int oldGridPosY, int oldGridPosX) {
    // 1. Check bounds and validity
        if (oldGridPosY < 0 || oldGridPosY >= tiles.size() ||
            oldGridPosX < 0 || oldGridPosX >= tiles[0].size() ||
            newGridPosY < 0 || newGridPosY >= tiles.size() ||
            newGridPosX < 0 || newGridPosX >= tiles[0].size() ||
            !tiles[oldGridPosY][oldGridPosX]) {
            return;
        }

        // 2. Move the tile
        tiles[newGridPosY][newGridPosX] = std::move(tiles[oldGridPosY][oldGridPosX]);
        
        // 3. Update the moved tile's position
        tiles[newGridPosY][newGridPosX]->setPosition(newGridPosX * tileSize, newGridPosY * tileSize);
        
        // 4. Update tileMap to maintain consistency
        tileMap[newGridPosY][newGridPosX] = tileMap[oldGridPosY][oldGridPosX];
        
        // 5. Create new walkable ground at old position
        tiles[oldGridPosY][oldGridPosX] = std::make_unique<WalkableGround>(oldGridPosX * tileSize, oldGridPosY * tileSize);
        tileMap[oldGridPosY][oldGridPosX] = 1; // Assuming 1 is walkable ground
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
    sf::Texture mirror1Texture;
    sf::Texture mirror2Texture;
    sf::Texture mirror3Texture;
    sf::Texture mirror4Texture;
    sf::Texture waterTileTexture;
};