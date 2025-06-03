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
public:
    Editor(int menuWinSizeX, int menuWinSizeY, bool editorWinClose) : button(menuWinSizeX, menuWinSizeY, editorWinClose) {}
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(button);
    }

    bool wasClicked() {
        return button.wasClicked();
    }

    void handleClick() {
        
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

        std::vector<std::vector<int>> tileMap;
        std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
        tiles.resize(16);


        for(int y= 0; y < 16; y++) {
            for(int x = 0; x < 16; x++) {
                tiles[y].resize(16);
                tiles[y][x] = std::make_unique<WalkableGround>(x*tileSize, y*tileSize, walkableTexture);
            }
        }

        while(window.isOpen()) {
            sf::Event event;
            while(window.pollEvent(event)) {
                if(event.type == sf::Event::Closed) {
                    window.close();
                    editorWinClose = true;
                }
            }
            window.clear();
            for(int i = 0; i < 16; i++) {
                for(int j = 0; j < 16; j++) {
                    window.draw(*tiles[i][j]);
                }
            }
            window.display();
        }

    }
};