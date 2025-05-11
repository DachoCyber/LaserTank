#include "include/map.h"
#include "include/extractMatrix.h"


#include "include/tile.h"
#include "include/destructibleBlock.h"
#include "include/mirror1Tile.h"
#include "include/mirror2Tile.h"
#include "include/mirror3Tile.h"
#include "include/mirror4Tile.h"
#include "include/waterTile.h"
#include "include/movableBlock.h"
#include "include/undestructableBlock.h"

#include "include/flag.h"

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
    if(!mirror3Texture.loadFromFile("Images/Mirror3WithBackground.png")) {
        throw std::runtime_error("Failed to load mirror 3 texture");
    }
    if(!mirror4Texture.loadFromFile("Images/Mirror4WithBackground.png")) {
        throw std::runtime_error("Failed to load mirror 4 texture");
    }
    if(!waterTileTexture.loadFromFile("Images/waterTile.png")) {
        throw std::runtime_error("Faild to load water tile texture");
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
                case 6:
                    tiles[y][x] = std::make_unique<Mirror3Tile>(x*tileSize, y*tileSize, mirror3Texture);
                    break;
                case 7:
                    tiles[y][x] = std::make_unique<Mirror4Tile>(x*tileSize, y*tileSize, mirror4Texture);
                    break;
                case 8:
                    tiles[y][x] = std::make_unique<WaterTile>(x*tileSize, y*tileSize, waterTileTexture);
                    waterTilesCoords.push_back(std::make_pair(y, x));
                    break;
                case 9:
                    tiles[y][x] = std::make_unique<MovableBlock>(x*tileSize, y*tileSize);
                    break;
                case 10:
                    tiles[y][x] = std::make_unique<Flag>(x*tileSize, y*tileSize);
                    flagCoordX = x*tileSize;
                    flagCoordY = y*tileSize;
                    break;
                case 11:
                    tiles[y][x] = std::make_unique<UndestructableBlock>(x*tileSize, y*tileSize);
                    break;
                default:
                    tiles[y][x] = nullptr; 
                    break;
            }
        
        }

    }
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    for (int y = 0; y < tiles.size(); y++) {
        for (int x = 0; x < tiles[y].size(); x++) {
            if (!tiles[y][x]) continue;

            // If this tile is NOT a WaterTile but there's a water tile below it
            bool isOnWater = tiles[y][x]->isUnderWater(waterTilesCoords);

            if (isOnWater) {
                // Draw water first
                WaterTile water(x * tileSize, y * tileSize, waterTileTexture);
                water.setAlpha(80);
                target.draw(*tiles[y][x]);
                target.draw(water);
            } else {

               target.draw(*tiles[y][x]);
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