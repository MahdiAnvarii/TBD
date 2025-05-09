#include "baloon.h"
#include "utils.h"

Baloon::Baloon(vector<vector<string>> theMap_, vector<pair<int,int>> roadMap_){
    theMap = theMap_;
    roadMap = roadMap_;
    baloonSpeed = 4;
    tile = roadMap[0];
    tileIndex = 0;
    if (tile.second==0){
        baloonX = -BALOON_SIZE_X;
        baloonY = MENU_Y + (tile.first-theMap.size()) * TILE_SIZE + (TILE_SIZE-BALOON_SIZE_Y)/2;
    } else if (tile.second==theMap[0].size()){
        baloonX = MENU_X + BALOON_SIZE_X;;
        baloonY = MENU_Y + (tile.first-theMap.size()) * TILE_SIZE + (TILE_SIZE-BALOON_SIZE_Y)/2;;
    } else if (tile.first==0){
        baloonX = tile.second * TILE_SIZE + (TILE_SIZE-BALOON_SIZE_X)/2;
        baloonY = -BALOON_SIZE_Y;
    } else{
        baloonX = tile.second * TILE_SIZE + (TILE_SIZE-BALOON_SIZE_X)/2;
        baloonY = MENU_Y + BALOON_SIZE_Y;
    }
}

void Baloon::update(){
    if (tileIndex+1 > roadMap.size()) return;
    else if (tileIndex+1 == roadMap.size()){
        tile.first+=deltaTile.first;
        tile.second+=deltaTile.second;
    } else{
        tile=roadMap[tileIndex];
        deltaTile = {
            roadMap[tileIndex+1].first - tile.first,
            roadMap[tileIndex+1].second - tile.second
        };
    }

    if (deltaTile==make_pair(0, 1)){
        baloonX+=baloonSpeed;
        if (baloonX>=(tile.second+1) * TILE_SIZE + (TILE_SIZE-BALOON_SIZE_X)/2) tileIndex+=1;
    }
    else if (deltaTile==make_pair(0, -1)){
        baloonX-=baloonSpeed;
        if (baloonX<=(tile.second-1) * TILE_SIZE + (TILE_SIZE-BALOON_SIZE_X)/2) tileIndex+=1;
    }
    else if (deltaTile==make_pair(1, 0)){
        baloonY+=baloonSpeed;
        if (baloonY>=MENU_Y + (tile.first+1-theMap.size()) * TILE_SIZE + (TILE_SIZE-BALOON_SIZE_Y)/2) tileIndex+=1;
    }
    else if (deltaTile == make_pair(-1, 0)){
        baloonY-=baloonSpeed;
        if (baloonY<=MENU_Y + (tile.first-1-theMap.size()) * TILE_SIZE + (TILE_SIZE-BALOON_SIZE_Y)/2) tileIndex+=1;
    }
}

void Baloon::render(RenderWindow& window){
    Texture simpleBaloonTexture;
    if (!simpleBaloonTexture.loadFromFile(SIMPLE_BALOON_ADDRESS)) {
        return;
    }
    Sprite simpleBaloonSprite;
    simpleBaloonSprite.setTexture(simpleBaloonTexture);
    Vector2u simpleBaloonTexSize = simpleBaloonSprite.getTexture()->getSize();
    float simpleBaloonScaleX = BALOON_SIZE_X / simpleBaloonTexSize.x;
    float simpleBaloonScaleY = BALOON_SIZE_Y / simpleBaloonTexSize.y;
    simpleBaloonSprite.setScale(simpleBaloonScaleX, simpleBaloonScaleY);
    simpleBaloonSprite.setPosition(baloonX, baloonY);
    window.draw(simpleBaloonSprite); 
}