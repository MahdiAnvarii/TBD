#include "baloon.h"
#include "utils.h"

Baloon::Baloon(const vector<vector<string>>& theMap_, const vector<pair<int,int>>& roadMap_, BaloonType baloonType_){
    theMap = theMap_;
    roadMap = roadMap_;
    baloonType = baloonType_;
    baloonSpeed = BALOON_SPEED;
    setBaloonType();
    tile = roadMap[0];
    tileIndex = 0;
    if (tile.second==0){
        baloonX = -baloonSizeX;
        baloonY = MENU_Y + (tile.first-theMap.size()) * TILE_SIZE + (TILE_SIZE-baloonSizeY)/2;
    } else if (tile.second==theMap[0].size()){
        baloonX = MENU_X + baloonSizeX;;
        baloonY = MENU_Y + (tile.first-theMap.size()) * TILE_SIZE + (TILE_SIZE-baloonSizeY)/2;;
    } else if (tile.first==0){
        baloonX = tile.second * TILE_SIZE + (TILE_SIZE-baloonSizeX)/2;
        baloonY = -baloonSizeY;
    } else{
        baloonX = tile.second * TILE_SIZE + (TILE_SIZE-baloonSizeX)/2;
        baloonY = MENU_Y + baloonSizeY;
    }
}

void Baloon::update(){
    if (frozen()) {
        if (freezeClock.getElapsedTime().asSeconds() >= freezeDuration) {
            isFrozen = false;
        }
        return;
    }

    if (tileIndex+1 > roadMap.size()){
        runAway = true;
        return;
    }
    else if (tileIndex+1 == roadMap.size() && !reachFinalTile){
        tile.first+=deltaTile.first;
        tile.second+=deltaTile.second;
        reachFinalTile = true;
    }
    else if (tileIndex+1 < roadMap.size()){
        tile=roadMap[tileIndex];
        deltaTile = {
            roadMap[tileIndex+1].first - tile.first,
            roadMap[tileIndex+1].second - tile.second
        };
    }

    if (deltaTile==make_pair(0, 1)){
        baloonX+=baloonSpeed;
        if (baloonX>=(tile.second+1) * TILE_SIZE + (TILE_SIZE-baloonSizeX)/2) tileIndex+=1;
    }
    else if (deltaTile==make_pair(0, -1)){
        baloonX-=baloonSpeed;
        if (baloonX<=(tile.second-1) * TILE_SIZE + (TILE_SIZE-baloonSizeX)/2) tileIndex+=1;
    }
    else if (deltaTile==make_pair(1, 0)){
        baloonY+=baloonSpeed;
        if (baloonY>=MENU_Y + (tile.first+1-theMap.size()) * TILE_SIZE + (TILE_SIZE-baloonSizeY)/2) tileIndex+=1;
    }
    else if (deltaTile == make_pair(-1, 0)){
        baloonY-=baloonSpeed;
        if (baloonY<=MENU_Y + (tile.first-1-theMap.size()) * TILE_SIZE + (TILE_SIZE-baloonSizeY)/2) tileIndex+=1;
    }
}

void Baloon::setBabyBaloon(Vector2f parentPosition, pair<int,int> tile_, int tileIndex_, pair<int, int> deltaTile_){
    baloonX = parentPosition.x;
    baloonY = parentPosition.y;
    tile = tile_;
    tileIndex = tileIndex_;
    deltaTile = deltaTile_;
}

void Baloon::setBaloonType(){
    if (baloonType==BaloonType::Simple){
        baloonSizeX = SIMPLE_BALOON_SIZE_X;
        baloonSizeY = SIMPLE_BALOON_SIZE_Y;
        if (!baloonTexture.loadFromFile(SIMPLE_BALOON_ADDRESS)) {
            return;
        }
    } else if (baloonType==BaloonType::Pregnant){
        baloonSizeX = PREGNANT_BALOON_SIZE_X;
        baloonSizeY = PREGNANT_BALOON_SIZE_Y;
        if (!baloonTexture.loadFromFile(PREGNANT_BALOON_ADDRESS)) {
            return;
        }
    }
}

void Baloon::render(RenderWindow& window){
    baloonSprite.setTexture(baloonTexture);
    Vector2u baloonTexSize = baloonSprite.getTexture()->getSize();
    float baloonScaleX = baloonSizeX / baloonTexSize.x;
    float baloonScaleY = baloonSizeY / baloonTexSize.y;
    baloonSprite.setScale(baloonScaleX, baloonScaleY);
    baloonSprite.setPosition(baloonX, baloonY);
    window.draw(baloonSprite); 
}

Sprite Baloon::getBaloonSprite() const { return baloonSprite; }
float Baloon::getBaloonSizeX() const { return baloonSizeX; }
float Baloon::getBaloonSizeY() const { return baloonSizeY; }

void Baloon::markAsDead() { isDead = true; }
bool Baloon::dead() const { return isDead; }
void Baloon::markAsFrozen() { 
    isFrozen = true;
    freezeClock.restart();
} 
bool Baloon::frozen() const { return isFrozen; }
BaloonType Baloon::getBaloonType() const { return baloonType; }
pair<int,int> Baloon::getBaloonTile() const { return tile; }
pair<int, int> Baloon::getBaloonDeltaTile() const { return deltaTile; }
int Baloon::getBaloonTileIndex() const { return tileIndex; }
bool Baloon::didYouRunAway() const { return runAway; }