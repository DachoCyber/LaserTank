#pragma once

#include "editorButton.h"


#include "../tile.h"
#include "../destructibleBlock.h"
#include "../mirror1Tile.h"
#include "../mirror2Tile.h"
#include "../mirror3Tile.h"
#include "../mirror4Tile.h"
#include "../waterTile.h"
#include "../movableBlock.h"
#include "../undestructableBlock.h"
#include "../tank1.h"
#include "../destroyedTank.h"
#include "../transportTrack.h"
#include "../tileInWater.h"

#include "../flag.h"

#include <vector>

class Editor : public sf :: Drawable {
public:

    bool editorWinClose = false;

    int tileSize = 32;

    EditorButton button;
    sf::Texture walkableTexture;
    sf::Texture destructibleTexture;
    sf::Texture mirror1Texture;
    sf::Texture mirror2Texture;
    sf::Texture mirror3Texture;
    sf::Texture mirror4Texture;
    sf::Texture waterTileTexture;
    sf::Texture flagTexture;
    sf::Texture movableBlockTexture;
    sf::Texture undestructableBlockTex;

    sf::Texture EnemyTank1UpTexture;
    sf::Texture EnemyTank1DownTexture;
    sf::Texture EnemyTank1LeftTexture;
    sf::Texture EnemyTank1RightTexture;

    sf::Texture destroyedTankUpTexture;
    sf::Texture destroyedTankDownTexture;
    sf::Texture destroyedTankLeftTexture;
    sf::Texture destroyedTankRightTexture;

    sf::Texture transportTrackLeftTex;
    sf::Texture transportTrackUpTex;
    sf::Texture transportTrackRightTex;
    sf::Texture transportTrackDownTex;

    sf::Texture tileInWaterTex;
    std::vector<std::vector<int>> tileMap;
public:
    Editor(int menuWinSizeX, int menuWinSizeY, bool editorWinClose) : button(menuWinSizeX, menuWinSizeY, editorWinClose) {}
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(button);
    }

    bool wasClicked() {
        return button.wasClicked();
    }

    void handleClick() {
        sf::Image destructibleBlock;        
        if(editorWinClose) return;

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

        int mapSizeX = 512;
        int windowSizeY = 512;
        int mapElementsSizeX = 96;
        int windowSizeX = mapSizeX + mapElementsSizeX;
        sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "Editor", sf::Style::Default);

        std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
        tiles.resize(16);

        
        sf::Sprite destructibleBlockSprite = createSprite(destructibleTexture, 16, 0, tileSize);
        sf::Sprite mirror1Sprite = createSprite(mirror1Texture, 17, 0, tileSize);   
        sf::Sprite mirror2Sprite = createSprite(mirror2Texture, 18, 0, tileSize);
        sf::Sprite mirror3Sprite = createSprite(mirror3Texture, 16, 1, tileSize);
        sf::Sprite mirror4Sprite = createSprite(mirror4Texture, 17, 1, tileSize);

        sf::Sprite waterSprite = createSprite(waterTileTexture, 18, 1, tileSize);
        sf::Sprite MovableBlockSprite = createSprite(movableBlockTexture, 16, 2, tileSize);
        sf::Sprite flagSprite = createSprite(flagTexture, 17,2, tileSize);
        sf::Sprite undestructableBlockSprite = createSprite(undestructableBlockTex, 18, 2, tileSize);

    tileMap.resize(16);
    for (int y = 0; y < 16; y++) {
        tiles[y].resize(16);
        tileMap[y].resize(16);
        for (int x = 0; x < 16; x++) {
            tiles[y][x] = std::make_unique<WalkableGround>(x * tileSize, y * tileSize, walkableTexture);
            
            tileMap[y][x] = 1;
        }
    }

    sf::Vector2i placedTile = {-1, -1};
    bool placingDestructible = false;
    bool placingMirror1Sprite = false;
    bool placingMirror3Sprite = false;
    bool placingMirror2Sprite = false;
    bool placingMirror4Sprite = false;
    bool placingWaterSprite = false;
    bool placingMovableBlock = false;
    bool placingFlagSprite = false;
    bool placingUndestructibleSprite = false;
    

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {

                window.close();
                editorWinClose = true;
            }

           if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                sf::Vector2i tileCoords = getTileCoords(window);
                int tileX = tileCoords.x;
                int tileY = tileCoords.y;

                if (destructibleBlockSprite.getGlobalBounds().contains(worldPos)) {
                    placingMovableBlock = false;
                    placingWaterSprite = false;
                    placingFlagSprite = false;
                    placingUndestructibleSprite = false;
                    placingDestructible = true;
                    placingMirror1Sprite = placingMirror2Sprite = placingMirror3Sprite = false;
                    placingMirror4Sprite = false;
                    tileMap[tileY][tileX] = 3;
                } else if (placingDestructible && tileX >= 0 && tileX < 16 && tileY >= 0 && tileY < 16) {
                    tileMap[tileY][tileX] = 1;
                    placeOrRemoveTile<DestructibleBlock>(tileX, tileY, 3, 1, tiles, tileMap, destructibleTexture);
                }

                if (mirror1Sprite.getGlobalBounds().contains(worldPos)) {
                    placingMirror1Sprite = true;
                    placingUndestructibleSprite = false;
                    placingMovableBlock = false;
                    placingFlagSprite = false;
                    placingWaterSprite = false;
                    placingDestructible = placingMirror2Sprite = placingMirror3Sprite = false;
                    placingMirror4Sprite = false;
                } else if (placingMirror1Sprite && tileX >= 0 && tileX < 16 && tileY >= 0 && tileY < 16) {
                    placeOrRemoveTile<Mirror1Tile>(tileX, tileY, 4, 1, tiles, tileMap, mirror1Texture);
                }

                if (mirror2Sprite.getGlobalBounds().contains(worldPos)) {
                    placingMovableBlock = false;
                    placingUndestructibleSprite = false;
                    placingFlagSprite = false;
                    placingMirror2Sprite = true;
                    placingWaterSprite = false;
                    placingDestructible = placingMirror1Sprite = placingMirror3Sprite = false;
                } else if (placingMirror2Sprite && tileX >= 0 && tileX < 16 && tileY >= 0 && tileY < 16) {
                    placeOrRemoveTile<Mirror2Tile>(tileX, tileY, 5, 1, tiles, tileMap, mirror2Texture);
                }

                if(mirror3Sprite.getGlobalBounds().contains(worldPos)) {
                    placingMirror3Sprite = true;
                    placingUndestructibleSprite = false;
                    placingMovableBlock = false;
                    placingFlagSprite = false;
                    placingWaterSprite = false;
                    placingDestructible = placingMirror1Sprite = placingMirror2Sprite = false;
                } else if (placingMirror3Sprite && tileX >= 0 && tileX < 16 && tileY >= 0 && tileY < 16) {
                    placeOrRemoveTile<Mirror3Tile>(tileX, tileY, 6, 1, tiles, tileMap, mirror3Texture);
                }

                if(mirror4Sprite.getGlobalBounds().contains(worldPos)) {
                    placingMirror4Sprite = true;
                    placingWaterSprite = false;
                    placingUndestructibleSprite = false;
                    placingFlagSprite = false;
                    placingMovableBlock = false;
                    placingDestructible = placingMirror1Sprite = placingMirror2Sprite = false;
                    placingMirror3Sprite = false;
                } else if (placingMirror4Sprite && tileX >= 0 && tileX < 16 && tileY >= 0 && tileY < 16) {
                    placeOrRemoveTile<Mirror4Tile>(tileX, tileY, 7, 1, tiles, tileMap, mirror4Texture);
                }
                if(waterSprite.getGlobalBounds().contains(worldPos)) {
                    placingMirror4Sprite = false;
                    placingUndestructibleSprite = false;
                    placingWaterSprite = true;
                    placingFlagSprite = false;
                    placingMovableBlock = false;
                    placingDestructible = placingMirror1Sprite = placingMirror2Sprite = false;
                    placingMirror3Sprite = false;
                } else if (placingWaterSprite && tileX >= 0 && tileX < 16 && tileY >= 0 && tileY < 16) {
                    placeOrRemoveTile<WaterTile>(tileX, tileY, 8, 1, tiles, tileMap, waterTileTexture);
                }
                if(MovableBlockSprite.getGlobalBounds().contains(worldPos)) {
                    placingMirror4Sprite = false;
                    placingUndestructibleSprite = false;
                    placingWaterSprite = false;
                    placingFlagSprite = false;
                    placingMovableBlock = true;
                    placingDestructible = placingMirror1Sprite = placingMirror2Sprite = false;
                    placingMirror3Sprite = false;
                } else if (placingMovableBlock && tileX >= 0 && tileX < 16 && tileY >= 0 && tileY < 16) {
                    placeOrRemoveTile<MovableBlock>(tileX, tileY, 9, 1, tiles, tileMap, movableBlockTexture);
                }
                if(flagSprite.getGlobalBounds().contains(worldPos)) {
                    placingMirror4Sprite = false;
                    placingUndestructibleSprite = false;
                    placingWaterSprite = false;
                    placingFlagSprite = true;
                    placingMovableBlock = false;
                    placingDestructible = placingMirror1Sprite = placingMirror2Sprite = false;
                    placingMirror3Sprite = false;
                } else if (placingFlagSprite && tileX >= 0 && tileX < 16 && tileY >= 0 && tileY < 16) {
                    placeOrRemoveTile<Flag>(tileX, tileY, 10, 1, tiles, tileMap, flagTexture);
                }

                if(undestructableBlockSprite.getGlobalBounds().contains(worldPos)) {
                    placingMirror4Sprite = false;
                    placingUndestructibleSprite = true;
                    placingWaterSprite = false;
                    placingFlagSprite = false;
                    placingMovableBlock = false;
                    placingDestructible = placingMirror1Sprite = placingMirror2Sprite = false;
                    placingMirror3Sprite = false;
                } else if (placingUndestructibleSprite && tileX >= 0 && tileX < 16 && tileY >= 0 && tileY < 16) {
                    placeOrRemoveTile<UndestructableBlock>(tileX, tileY, 11, 1, tiles, tileMap, undestructableBlockTex);
                }
            }

        }

        window.clear();
        for (int y = 0; y < 16; ++y)
            for (int x = 0; x < 16; ++x)
                window.draw(*tiles[y][x]);

        window.draw(destructibleBlockSprite);
        window.draw(mirror1Sprite);
        window.draw(mirror2Sprite);
        window.draw(mirror3Sprite);
        window.draw(mirror4Sprite);
        window.draw(waterSprite);
        window.draw(MovableBlockSprite);
        window.draw(flagSprite);
        window.draw(undestructableBlockSprite);
        window.display();
    }

    }

    sf::Vector2i getTileCoords(sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
        return { static_cast<int>(worldPos.x) / tileSize, static_cast<int>(worldPos.y) / tileSize };
    }

    template<typename TileType>
    void placeOrRemoveTile(
        int tileX, int tileY, 
        int placeID, int removeID,
        std::vector<std::vector<std::unique_ptr<Tile>>>& tiles,
        std::vector<std::vector<int>>& tileMap,
        sf::Texture& tileTexture
    ) 
    {

        if (dynamic_cast<TileType*>(tiles[tileY][tileX].get())) {
            tileMap[tileY][tileX] = removeID;
            tiles[tileY][tileX] = std::make_unique<WalkableGround>(tileX * tileSize, tileY * tileSize, walkableTexture);
        } else {
            tileMap[tileY][tileX] = placeID;
            tiles[tileY][tileX] = std::make_unique<TileType>(tileX * tileSize, tileY * tileSize, tileTexture);
        }
    }

    sf::Sprite createSprite(sf::Texture& texture, int gridX, int gridY, int tileSize) {
    sf::Sprite sprite(texture);
    sprite.setScale(sf::Vector2f(
        tileSize / sprite.getGlobalBounds().width,
        tileSize / sprite.getGlobalBounds().height
    ));
    sprite.setPosition(static_cast<float>(gridX * tileSize), static_cast<float>(gridY * tileSize));
    return sprite;
}



};