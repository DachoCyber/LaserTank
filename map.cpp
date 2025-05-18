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
#include "include/tank1.h"
#include "include/destroyedTank.h"
#include "include/transportTrack.h"
#include "include/tileInWater.h"

#include "include/flag.h"

#include <stdexcept>
#include <fstream>
#include <sstream>

Map::Map(int level) {
    readMapFromXML(tileMap, level);

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
                case 0:
                    playerPosX = x;
                    playerPosY = y;
                    std::cout << playerPosX << " " << playerPosX << std::endl;
                    tiles[y][x] = std::make_unique<WalkableGround>(x*tileSize, y*tileSize);
                    break;
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
                case 12: 
                    tiles[y][x] = std::make_unique<EnemyTank1>(x*tileSize, y*tileSize, 0);
                    break;
                case 13:
                    tiles[y][x] = std::make_unique<EnemyTank1>(x*tileSize, y*tileSize, 1);
                    break;
                case 14:
                    tiles[y][x] = std::make_unique<EnemyTank1>(x*tileSize, y*tileSize, 2);
                    break;
                case 15:
                    tiles[y][x] = std::make_unique<EnemyTank1>(x*tileSize, y*tileSize, 3);
                    break;
                case 16: 
                    tiles[y][x] = std::make_unique<DestroyedTank>(x*tileSize, y*tileSize, 0);
                    break;
                case 17:
                    tiles[y][x] = std::make_unique<DestroyedTank>(x*tileSize, y*tileSize, 1);
                    break;
                case 18:
                    tiles[y][x] = std::make_unique<DestroyedTank>(x*tileSize, y*tileSize, 2);
                    break;
                case 19:
                    tiles[y][x] = std::make_unique<DestroyedTank>(x*tileSize, y*tileSize, 3);
                    break;
                case 20:
                    tiles[y][x] = std::make_unique<TransportTrack>(x*tileSize, y*tileSize, LEFT);
                    trackTileCoords.push_back(std::make_tuple(y, x, LEFT));
                    break;
                case 21:
                    tiles[y][x] = std::make_unique<TransportTrack>(x*tileSize, y*tileSize, RIGHT);
                    trackTileCoords.push_back(std::make_tuple(y, x, RIGHT));
                    break;
                case 22:
                    tiles[y][x] = std::make_unique<TransportTrack>(x*tileSize, y*tileSize, UP);
                    trackTileCoords.push_back(std::make_tuple(y, x, UP));
                    break;
                case 23:
                    tiles[y][x] = std::make_unique<TransportTrack>(x*tileSize, y*tileSize, DOWN);
                    trackTileCoords.push_back(std::make_tuple(y, x, DOWN));
                    break;
                default:
                    tiles[y][x] = nullptr; 
                    break;
            }
        
        }

    }
}


void Map :: destroyTank(int bulletGridPosX, int bulletGridPosY, int tankType) {
    switch(tankType) {
        case 1:
            tiles[bulletGridPosY][bulletGridPosX] = std::make_unique<DestroyedTank>(bulletGridPosX*tileSize, bulletGridPosY*tileSize, 0);
            break;
        case 2:
            tiles[bulletGridPosY][bulletGridPosX] = std::make_unique<DestroyedTank>(bulletGridPosX*tileSize, bulletGridPosY*tileSize, 1);
            break;
        case 3:
            tiles[bulletGridPosY][bulletGridPosX] = std::make_unique<DestroyedTank>(bulletGridPosX*tileSize, bulletGridPosY*tileSize, 2);
            break;
        case 4:
            tiles[bulletGridPosY][bulletGridPosX] = std::make_unique<DestroyedTank>(bulletGridPosX*tileSize, bulletGridPosY*tileSize, 3);
            break;
    }
    
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    for (int y = 0; y < tiles.size(); y++) {
        for (int x = 0; x < tiles[y].size(); x++) {
            if (!tiles[y][x]) continue;

            target.draw(*tiles[y][x]);
               


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

void Map::updateTransportTracks() {
    for (auto& coord : trackTileCoords) {
        int y = std::get<0>(coord);
        int x = std::get<1>(coord);
        Direction dir = std::get<2>(coord);
        
        if (!tiles[y][x]->isTransportTrack() && tiles[y][x]->isWalkableGround()) {
            tiles[y][x] = std::make_unique<TransportTrack>(x * tileSize, y * tileSize, dir);
        }
    }
}

void Map :: updateWaterTiles() {
    for(auto it = waterTilesCoords.begin(); it != waterTilesCoords.end(); it++) {
        int x = it -> second;
        int y = it -> first;
        if(tiles[y][x] -> isTileMovableBlock()) {
            tiles[y][x] = std::make_unique<TileInWater>(x*tileSize, y*tileSize);
            waterTilesCoords.erase(it);
            tilesInWaterCoords.push_back(std::make_pair(y, x));
            std::cout << "pushing tiles in water coords" << y << " " << x << " aaaaaaaaaa" << tilesInWaterCoords.size()<< std::endl;
            return;
        }
    }
}