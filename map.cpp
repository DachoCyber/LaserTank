#include "include/map.h"
#include "include/extractMatrix.h"


#include "include/tile.h"
#include "include/destructibleBlock.h"
#include "include/mirror1Tile.h"
#include "include/mirror2Tile.h"

#include <stdexcept>
#include <fstream>
#include <sstream>

Map::Map() {
    readMapFromXML(tileMap);

    tiles.resize(mapHeight);
    for (int y = 0; y < mapHeight; ++y) {
        tiles[y].resize(mapWidth);
    }
    
    loadTextures();
    buildMap();
}

void Map::loadTextures() {
    if (!walkableTexture.loadFromFile("Images/walkableGround.png")) {
        throw std::runtime_error("Failed to load walkable texture");
    }
    if (!destructibleTexture.loadFromFile("Images/destructibleBlock.png")) {
        throw std::runtime_error("Failed to load destructible texture");
    }
    if(!mirror1Texture.loadFromFile("Images/Mirror1WithBackground.png")) {
        throw std::runtime_error("Failed to load mirror 1 texture");
    }
    if(!mirror2Texture.loadFromFile("Images/Mirror2WithBackground.png")) {
        throw std::runtime_error("Failed to load mirror 2 texture");
    }
}

void Map::buildMap() {
    

    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            switch(tileMap[y][x]) {
                case 1:
                    tiles[y][x] = std::make_unique<WalkableGround>(x*tileSize, y*tileSize);
                    
                    break;
                case 3:
                    tiles[y][x] = std::make_unique<DestructibleBlock>(x*tileSize, y*tileSize);
                    break;
                case 4:
                    tiles[y][x] = std::make_unique<Mirror1Tile>(x*tileSize, y*tileSize, mirror1Texture);
                    break;
                case 5: 
                    tiles[y][x] = std::make_unique<Mirror2Tile>(x*tileSize, y*tileSize, mirror2Texture);
                    break;
                default:
                    tiles[y][x] = nullptr; 
                    break;
            }
        
        }

    }
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for(int i = 0; i < tiles.size(); i++) {
        for(int j = 0; j < tiles[i].size(); j++) {
            if(tiles[i][j]) {
                target.draw(*tiles[i][j]);
            }
        }
    }
}

bool Map::isWalkable(int x, int y) const {
    if (x < 0 || x >= mapWidth || y < 0 || y >= mapHeight) {
        return false;
    }
    int tile = tileMap[y][x];
    return (tile == 1 || tile == 2 || tile == 5 || tile == 6);
}

sf::Vector2f Map::getTilePosition(int x, int y) const {
    return sf::Vector2f(x * tileSize, y * tileSize);
}