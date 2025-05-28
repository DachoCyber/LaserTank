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
        throw std::runtime_error("Failed to load water tile texture");
    }
    if(!movableBlockTexture.loadFromFile("Images/MovableBlock.png")) {
        throw std::runtime_error("Failed to load water tile texture");
    }
    if(!flagTexture.loadFromFile("Images/flagWithBackground.png")) {
        throw std::runtime_error("Failed to load flag texture");
    }
    if(!undestructableBlockTex.loadFromFile("Images/undestructibleBlock.png")) {
        throw std::runtime_error("Failed to load undestructible block texture");
    }
    if(!EnemyTank1LeftTexture.loadFromFile("Images/tank1.png")) {
        throw std::runtime_error("Failed to load enemy tank left texture");
    }
    if(!EnemyTank1RightTexture.loadFromFile("Images/tank2.png")) {
        throw std::runtime_error("Failed to load enemy tank left texture");
    }
    if(!EnemyTank1UpTexture.loadFromFile("Images/tank3.png")) {
        throw std::runtime_error("Failed to load enemy tank up texture");
    }
    if(!EnemyTank1DownTexture.loadFromFile("Images/tank4.png")) {
        throw std::runtime_error("Failed to load enemy tank down texture");
    }
    if(!destroyedTankLeftTexture.loadFromFile("Images/destroyedTank1.png")) {
        throw std::runtime_error("Failed to load destoryed tank left texutre");
    }
    if(!destroyedTankUpTexture.loadFromFile("Images/destroyedTank2.png")) {
        throw std::runtime_error("Failed to load destoryed tank left texutre");
    }
    if(!destroyedTankDownTexture.loadFromFile("Images/destroyedTank3.png")) {
        throw std::runtime_error("Failed to load destoryed tank left texutre");
    }
    if(!destroyedTankRightTexture.loadFromFile("Images/destroyedTank4.png")) {
        throw std::runtime_error("Failed to load destoryed tank left texutre");
    }
    if(!transportTrackDownTex.loadFromFile("Images/transportTrack4.png")) {
        throw std::runtime_error("Failed to load transport track texture");
    }
    if(!transportTrackUpTex.loadFromFile("Images/transportTrack3.png")) {
        throw std::runtime_error("Failed to load transport track 3 texture");
    }
    if(!transportTrackRightTex.loadFromFile("Images/transportTrack2.png")) {
        throw std::runtime_error("Failed to load transport track 3 texture");
    }
    if(!transportTrackLeftTex.loadFromFile("Images/transportTrack.png")) {
        throw std::runtime_error("Failed to load transport track 3 texture");
    }
    if(!tileInWaterTex.loadFromFile("Images/tileInWater.png")) {
        throw std::runtime_error("Failed to load tile in water texture");
    }

}


void Map::buildMap() {
    

    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            switch(tileMap[y][x]) {
                case 0:
                    playerPosX = x;
                    playerPosY = y;
                    tiles[y][x] = std::make_unique<WalkableGround>(x*tileSize, y*tileSize, walkableTexture);
                    break;
                case 1:
                    tiles[y][x] = std::make_unique<WalkableGround>(x*tileSize, y*tileSize, walkableTexture);
                    
                    break;
                case 3:
                    tiles[y][x] = std::make_unique<DestructibleBlock>(x*tileSize, y*tileSize, destructibleTexture);
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
                    tiles[y][x] = std::make_unique<MovableBlock>(x*tileSize, y*tileSize, movableBlockTexture);
                    break;
                case 10:
                    tiles[y][x] = std::make_unique<Flag>(x*tileSize, y*tileSize, flagTexture);
                    flagCoordX = x*tileSize;
                    flagCoordY = y*tileSize;
                    break;
                case 11:
                    tiles[y][x] = std::make_unique<UndestructableBlock>(x*tileSize, y*tileSize, undestructableBlockTex);
                    break;
                case 12: 
                    tiles[y][x] = std::make_unique<EnemyTank1>(x*tileSize, y*tileSize, 0, EnemyTank1LeftTexture);
                    break;
                case 13:
                    tiles[y][x] = std::make_unique<EnemyTank1>(x*tileSize, y*tileSize, 1, EnemyTank1RightTexture);
                    break;
                case 14:
                    tiles[y][x] = std::make_unique<EnemyTank1>(x*tileSize, y*tileSize, 2, EnemyTank1UpTexture);
                    break;
                case 15:
                    tiles[y][x] = std::make_unique<EnemyTank1>(x*tileSize, y*tileSize, 3, EnemyTank1DownTexture);
                    break;
                case 16: 
                    tiles[y][x] = std::make_unique<DestroyedTank>(x*tileSize, y*tileSize, 0, destroyedTankLeftTexture);
                    break;
                case 17:
                    tiles[y][x] = std::make_unique<DestroyedTank>(x*tileSize, y*tileSize, 1, destroyedTankUpTexture);
                    break;
                case 18:
                    tiles[y][x] = std::make_unique<DestroyedTank>(x*tileSize, y*tileSize, 2, destroyedTankDownTexture);
                    break;
                case 19:
                    tiles[y][x] = std::make_unique<DestroyedTank>(x*tileSize, y*tileSize, 3, destroyedTankRightTexture);
                    break;
                case 20:
                    tiles[y][x] = std::make_unique<TransportTrack>(x*tileSize, y*tileSize, LEFT, transportTrackLeftTex);
                    trackTileCoords.push_back(std::make_tuple(y, x, LEFT));
                    break;
                case 21:
                    tiles[y][x] = std::make_unique<TransportTrack>(x*tileSize, y*tileSize, RIGHT, transportTrackRightTex);
                    trackTileCoords.push_back(std::make_tuple(y, x, RIGHT));
                    break;
                case 22:
                    tiles[y][x] = std::make_unique<TransportTrack>(x*tileSize, y*tileSize, UP, transportTrackUpTex);
                    trackTileCoords.push_back(std::make_tuple(y, x, UP));
                    break;
                case 23:
                    tiles[y][x] = std::make_unique<TransportTrack>(x*tileSize, y*tileSize, DOWN, transportTrackDownTex);
                    trackTileCoords.push_back(std::make_tuple(y, x, DOWN));
                    break;
                case 50:
                    tiles[y][x] = std::make_unique<TileInWater>(x*tileSize, y*tileSize, tileInWaterTex);
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
            tiles[bulletGridPosY][bulletGridPosX] = std::make_unique<DestroyedTank>(bulletGridPosX*tileSize, bulletGridPosY*tileSize, 0, destroyedTankLeftTexture);
            break;
        case 2:
            tiles[bulletGridPosY][bulletGridPosX] = std::make_unique<DestroyedTank>(bulletGridPosX*tileSize, bulletGridPosY*tileSize, 1, destroyedTankDownTexture);
            break;
        case 3:
            tiles[bulletGridPosY][bulletGridPosX] = std::make_unique<DestroyedTank>(bulletGridPosX*tileSize, bulletGridPosY*tileSize, 2, destroyedTankUpTexture);
            break;
        case 4:
            tiles[bulletGridPosY][bulletGridPosX] = std::make_unique<DestroyedTank>(bulletGridPosX*tileSize, bulletGridPosY*tileSize, 3, destroyedTankRightTexture);
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
            switch(dir) {
                case LEFT:
                    tiles[y][x] = std::make_unique<TransportTrack>(x * tileSize, y * tileSize, dir, transportTrackLeftTex);
                    break;
                case RIGHT:
                    tiles[y][x] = std::make_unique<TransportTrack>(x * tileSize, y * tileSize, dir, transportTrackRightTex);
                    break;
                case UP:
                    tiles[y][x] = std::make_unique<TransportTrack>(x * tileSize, y * tileSize, dir, transportTrackUpTex);
                    break;
                case DOWN:
                    tiles[y][x] = std::make_unique<TransportTrack>(x * tileSize, y * tileSize, dir, transportTrackDownTex);
                    break;
            }
            
        }
    }
}

void Map :: updateWaterTiles() {
    for(auto it = waterTilesCoords.begin(); it != waterTilesCoords.end(); it++) {
        int x = it -> second;
        int y = it -> first;
        if(tiles[y][x] -> isTileMovableBlock()) {
            tiles[y][x] = std::make_unique<TileInWater>(x*tileSize, y*tileSize, tileInWaterTex);
            //tileMap[y][x] = 50;
            waterTilesCoords.erase(it);
            //std::cout << "adding tile" << y << " " << x << std::endl;
            tilesInWaterCoords.push_back(std::make_pair(y, x));
            erasedWaterTiles.push_back(std::make_pair(y, x));
            //std::cout << "pushing tiles in water coords" << y << " " << x << " aaaaaaaaaa" << tilesInWaterCoords.size()<< std::endl;
            return;
        }
    }
}

void Map :: moveTile(int newGridPosY, int newGridPosX, int oldGridPosY, int oldGridPosX) {
    // 1. Check bounds and validity
        if (oldGridPosY < 0 || oldGridPosY >= tiles.size() ||
            oldGridPosX < 0 || oldGridPosX >= tiles[0].size() ||
            newGridPosY < 0 || newGridPosY >= tiles.size() ||
            newGridPosX < 0 || newGridPosX >= tiles[0].size() ||
            !tiles[oldGridPosY][oldGridPosX]) {
            return;
        }

        

        /*for(auto it = waterTilesCoords.begin(); it != waterTilesCoords.end(); it++) {
                if(it -> first == newGridPosY && it -> second == newGridPosX) {
                    //if(!exists) {

                        tiles[oldGridPosY][oldGridPosX] = std::make_unique<WalkableGround>(oldGridPosX * tileSize, oldGridPosY * tileSize);
                    /*} else {
                        tiles[oldGridPosY][oldGridPosX] = std::make_unique<TileInWater>(oldGridPosX*tileSize, oldGridPosY*tileSize);
                    }*/      
          //      }
        //}

        if(tiles[oldGridPosY][oldGridPosX] -> isTileInWater() || tiles[oldGridPosY][oldGridPosX] -> isMovableTypeOfBlock()) {
           // std::cout << "eeeeeeee" << std::endl;
            // Check if we're moving from a position that was originally water
        bool wasWaterTile = false;
        for (auto it = tilesInWaterCoords.begin(); it != tilesInWaterCoords.end(); ++it) {
            if (it->first == oldGridPosY && it->second == oldGridPosX) {
                wasWaterTile = true;
                //std::cout << "was water tile on position  " << oldGridPosX << " " << oldGridPosY << std::endl;
                tilesInWaterCoords.erase(it);
                break;
            }
        }

        // Check if we're moving to a water tile
        bool movingToWater = false;
        for (auto it = waterTilesCoords.begin(); it != waterTilesCoords.end(); ++it) {
            if (it->first == newGridPosY && it->second == newGridPosX) {
                movingToWater = true;
                //std::cout << "moving to water to position  " << newGridPosY << " " << newGridPosX << std::endl;
                break;
            }
        }
        bool wasGround = !(tiles[oldGridPosY][oldGridPosX] -> isWater());
        //movingToWater = true;
        if(!movingToWater) {
        }
        bool erasedWaterTilesExists = false;
        for(int i = 0; i < erasedWaterTiles.size(); i++) {
            if(oldGridPosX == erasedWaterTiles[i].second && oldGridPosY == erasedWaterTiles[i].first) {
                erasedWaterTilesExists = true;
            }
        }
        // 2. Move the tile
        tiles[newGridPosY][newGridPosX] = std::move(tiles[oldGridPosY][oldGridPosX]);
        
        // 3. Update the moved tile's position
        tiles[newGridPosY][newGridPosX]->setPosition(newGridPosX * tileSize, newGridPosY * tileSize);
        
        // 4. Update tileMap to maintain consistency
        tileMap[newGridPosY][newGridPosX] = tileMap[oldGridPosY][oldGridPosX];
        
        // 5. Handle the old position
        if ((wasWaterTile && movingToWater)) {
            // Restore the water tile
            tiles[oldGridPosY][oldGridPosX] = std::make_unique<TileInWater>(oldGridPosX * tileSize, oldGridPosY * tileSize, tileInWaterTex);
            tileMap[oldGridPosY][oldGridPosX] = 50;/* whatever value represents water tiles */
            //std::cout << "jeste " << std::endl;
        } else {
            // Create new walkable ground at old position
                if(erasedWaterTilesExists) {
                    tiles[oldGridPosY][oldGridPosX] = std::make_unique<TileInWater>(oldGridPosX * tileSize, oldGridPosY * tileSize, tileInWaterTex);
                    tileMap[oldGridPosY][oldGridPosX] = 50;
                }
                else {

                    tiles[oldGridPosY][oldGridPosX] = std::make_unique<WalkableGround>(oldGridPosX * tileSize, oldGridPosY * tileSize, walkableTexture);
                    tileMap[oldGridPosY][oldGridPosX] = 1; // Assuming 1 is walkable ground
                }
            //std::cout << "hereeeee" << std::endl;
            
            // If we moved to a water tile, remember the original position
            if (movingToWater) {
                tilesInWaterCoords.emplace_back(oldGridPosY, oldGridPosX);
            }
        }
        }

        else {
            //std::cout <<" aaaaaa" << std::endl;
            for(auto it = waterTilesCoords.begin(); it != waterTilesCoords.end(); it++) {
                if(it -> first == newGridPosY && it -> second == newGridPosX) {
                    //if(!exists) {

                        tiles[oldGridPosY][oldGridPosX] = std::make_unique<WalkableGround>(oldGridPosX * tileSize, oldGridPosY * tileSize, walkableTexture);
                        tileMap[oldGridPosY][oldGridPosX] = 1;
                    /*} else {
                        tiles[oldGridPosY][oldGridPosX] = std::make_unique<TileInWater>(oldGridPosX*tileSize, oldGridPosY*tileSize);
                    }*/
                    return;        
                } 
            }
             tiles[newGridPosY][newGridPosX] = std::move(tiles[oldGridPosY][oldGridPosX]);
        
        // 3. Update the moved tile's position
        tiles[newGridPosY][newGridPosX]->setPosition(newGridPosX * tileSize, newGridPosY * tileSize);
        
        // 4. Update tileMap to maintain consistency
        tileMap[newGridPosY][newGridPosX] = tileMap[oldGridPosY][oldGridPosX];
        
        // 5. Create new walkable ground at old position
        tiles[oldGridPosY][oldGridPosX] = std::make_unique<WalkableGround>(oldGridPosX * tileSize, oldGridPosY * tileSize, walkableTexture);
        tileMap[oldGridPosY][oldGridPosX] = 1; // Assuming 1 is walkable ground

        }
        std::cout  << "HERE" << oldGridPosY <<  " " <<  oldGridPosX << " " << tileMap[oldGridPosY][oldGridPosX] << std::endl;
        std::cout << "HERE" << newGridPosY << " " << newGridPosX <<" " << tileMap[newGridPosY][newGridPosX] << std::endl; 
    }

    Tile* Map :: getTileFromUniquePtr(std::unique_ptr<Tile> tile) const {
        return tile.get();
    }

    std::vector<std::vector<int>> Map::getMapState() const {
        std::vector<std::vector<int>> mapState(mapHeight); // Initialize outer vector with mapHeight empty vectors
        
        for(int i = 0; i < mapHeight; i++) {
            mapState[i].reserve(mapWidth); // Optional but recommended for performance
            for(int j = 0; j < mapWidth; j++) {
                mapState[i].push_back(tiles[i][j] -> code());
            }
        }
        return mapState;
    }

    void Map::setTilesEl(size_t i, size_t j, std::unique_ptr<Tile> newElement) {
        if (i < tiles.size() && j < tiles[i].size()) {
            tiles[i][j] = std::move(newElement);
        } else {
        }
    }

    void Map :: undoMove(std::vector<std::vector<int>> lastMapState) {
        for (int y = 0; y < mapHeight; y++) {
            for (int x = 0; x < mapWidth; x++) {
                std::unique_ptr<Tile> tile;
                switch(lastMapState[y][x]) {
                    case 0:
                        tile = std::make_unique<WalkableGround>(x*tileSize, y*tileSize, walkableTexture);
                        break;
                    case 1:
                        tile = std::make_unique<WalkableGround>(x*tileSize, y*tileSize, walkableTexture);
                        
                        break;
                    case 3:
                        tile = std::make_unique<DestructibleBlock>(x*tileSize, y*tileSize, destructibleTexture);
                        break;
                    case 4:
                        tile = std::make_unique<Mirror1Tile>(x*tileSize, y*tileSize, mirror1Texture);
                        break;
                    case 5: 
                        tile = std::make_unique<Mirror2Tile>(x*tileSize, y*tileSize, mirror2Texture);
                        break;
                    case 6:
                        tile = std::make_unique<Mirror3Tile>(x*tileSize, y*tileSize, mirror3Texture);
                        break;
                    case 7:
                        tile = std::make_unique<Mirror4Tile>(x*tileSize, y*tileSize, mirror4Texture);
                        break;
                    case 8:
                        tile = std::make_unique<WaterTile>(x*tileSize, y*tileSize, waterTileTexture);
                        waterTilesCoords.push_back(std::make_pair(y, x));
                        break;
                    case 9:
                        tile = std::make_unique<MovableBlock>(x*tileSize, y*tileSize, movableBlockTexture);
                        break;
                    case 10:
                        tile = std::make_unique<Flag>(x*tileSize, y*tileSize, flagTexture);
                        flagCoordX = x*tileSize;
                        flagCoordY = y*tileSize;
                        break;
                    case 11:
                        tile = std::make_unique<UndestructableBlock>(x*tileSize, y*tileSize, undestructableBlockTex);
                        break;
                    case 12: 
                        tile = std::make_unique<EnemyTank1>(x*tileSize, y*tileSize, 0, EnemyTank1LeftTexture);
                        break;
                    case 13:
                        tile = std::make_unique<EnemyTank1>(x*tileSize, y*tileSize, 1, EnemyTank1RightTexture);
                        break;
                    case 14:
                        tile = std::make_unique<EnemyTank1>(x*tileSize, y*tileSize, 2, EnemyTank1UpTexture);
                        break;
                    case 15:
                        tile = std::make_unique<EnemyTank1>(x*tileSize, y*tileSize, 3, EnemyTank1DownTexture);
                        break;
                    case 16: 
                        tile = std::make_unique<DestroyedTank>(x*tileSize, y*tileSize, 0, destroyedTankLeftTexture);
                        break;
                    case 17:
                        tile = std::make_unique<DestroyedTank>(x*tileSize, y*tileSize, 1, destroyedTankUpTexture);
                        break;
                    case 18:
                        tile = std::make_unique<DestroyedTank>(x*tileSize, y*tileSize, 2, destroyedTankDownTexture);
                        break;
                    case 19:
                        tile = std::make_unique<DestroyedTank>(x*tileSize, y*tileSize, 3, destroyedTankRightTexture);
                        break;
                    case 20:
                        tile = std::make_unique<TransportTrack>(x*tileSize, y*tileSize, LEFT, transportTrackLeftTex);
                        trackTileCoords.push_back(std::make_tuple(y, x, LEFT));
                        break;
                    case 21:
                        tile = std::make_unique<TransportTrack>(x*tileSize, y*tileSize, RIGHT, transportTrackRightTex);
                        trackTileCoords.push_back(std::make_tuple(y, x, RIGHT));
                        break;
                    case 22:
                        tile = std::make_unique<TransportTrack>(x*tileSize, y*tileSize, UP, transportTrackUpTex);
                        trackTileCoords.push_back(std::make_tuple(y, x, UP));
                        break;
                    case 23:
                        tile = std::make_unique<TransportTrack>(x*tileSize, y*tileSize, DOWN, transportTrackDownTex);
                        trackTileCoords.push_back(std::make_tuple(y, x, DOWN));
                        break;
                    case 50:
                        tile = std::make_unique<TileInWater>(x*tileSize, y*tileSize, tileInWaterTex);
                        break;
                    default:
                        tile = nullptr; 
                        break;
                }
                if(y * 16 + x == 235 || y*16 + x == 219) {

                std::cout << "here" << y << " " << x<<" " << tileMap[y][x] << std::endl;
                }
                tiles[y][x] = std::move(tile);
            }
        }
    }