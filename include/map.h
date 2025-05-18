#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <utility>
#include <list>

#include "tile.h"
#include "walkableGround.h"
#include "tileInWater.h"
#include "waterTile.h"

class Map : public sf::Drawable {
public:
    Map(int level);
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
    void updateWaterTiles();
    void destroyTank(int bulletGridPosX, int bulletGridPosY, int tankType);
    void moveTile(int newGridPosY, int newGridPosX, int oldGridPosY, int oldGridPosX) {
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
        //movingToWater = true;
        if(!movingToWater) {
            std::cout <<" not moving to water tile" << std::endl << std::endl;
        }


        // 2. Move the tile
        tiles[newGridPosY][newGridPosX] = std::move(tiles[oldGridPosY][oldGridPosX]);
        
        // 3. Update the moved tile's position
        tiles[newGridPosY][newGridPosX]->setPosition(newGridPosX * tileSize, newGridPosY * tileSize);
        
        // 4. Update tileMap to maintain consistency
        tileMap[newGridPosY][newGridPosX] = tileMap[oldGridPosY][oldGridPosX];
        

        // 5. Handle the old position
        if (wasWaterTile && movingToWater) {
            // Restore the water tile
            tiles[oldGridPosY][oldGridPosX] = std::make_unique<TileInWater>(oldGridPosX * tileSize, oldGridPosY * tileSize);
            tileMap[oldGridPosY][oldGridPosX] = 8;/* whatever value represents water tiles */
            //std::cout << "jeste " << std::endl;
        } else {
            // Create new walkable ground at old position
            tiles[oldGridPosY][oldGridPosX] = std::make_unique<WalkableGround>(oldGridPosX * tileSize, oldGridPosY * tileSize);
            tileMap[oldGridPosY][oldGridPosX] = 1; // Assuming 1 is walkable ground
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

                        tiles[oldGridPosY][oldGridPosX] = std::make_unique<WalkableGround>(oldGridPosX * tileSize, oldGridPosY * tileSize);
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
        tiles[oldGridPosY][oldGridPosX] = std::make_unique<WalkableGround>(oldGridPosX * tileSize, oldGridPosY * tileSize);
        tileMap[oldGridPosY][oldGridPosX] = 1; // Assuming 1 is walkable ground
        }
        
    }
    int getFlagCoordX() const {return flagCoordX;}
    int getFlagCoordY() const {return flagCoordY;}
    int getPlayerPositionX() const {return playerPosX;}
    int getPlayerPositionY() const {return playerPosY;}

    void updateTransportTracks();

    std::vector<std::tuple<int, int, Direction>> getTrackCoord() const {return trackTileCoords;}

private:
    void loadTextures();
    void buildMap();

    const int tileSize = 32;
    const int mapWidth = 16;
    const int mapHeight = 16;

    int playerPosX;
    int playerPosY;
    
    std::list<std::pair<int, int>> waterTilesCoords;
    
    std::vector<std::vector<int>> tileMap;
    std::vector<std::vector<sf::Sprite>> sprites;
    std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
    std::vector<std::pair<int, int>> tileInWater;
    
    sf::Texture walkableTexture;
    sf::Texture destructibleTexture;
    sf::Texture mirror1Texture;
    sf::Texture mirror2Texture;
    sf::Texture mirror3Texture;
    sf::Texture mirror4Texture;
    sf::Texture waterTileTexture;
    sf::Texture flagTexture;

    std::vector<std::tuple<int, int, Direction>> trackTileCoords;

    std::vector<std::pair<int, int>> tilesInWaterCoords;

    int level;

    int flagCoordX, flagCoordY;
};