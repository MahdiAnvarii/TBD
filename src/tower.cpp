#include "tower.h"
#include "utils.h"
#include "baloon.h"
#include <cmath>

Tower::Tower(int row_, int col_, int towerPrice_, TowerType towerType_){
    row = row_;
    col = col_;
    towerPrice = towerPrice_;
    towerType = towerType_;
    towerX = col * TILE_SIZE;
    towerY = (row + 1) * TILE_SIZE;
    setTowerType();
}

void Tower::setTowerType(){
    if (towerType==TowerType::Simple){
        towerBoard=180;
        cooldownTime = 0.5f;
        if (!towerTexture.loadFromFile(SIMPLE_TOWER_ADDRESS)) {
            return;
        }
    } else if (towerType==TowerType::Ice){
        towerBoard=150;
        cooldownTime = 1.0f;
        if (!towerTexture.loadFromFile(ICE_TOWER_ADDRESS)) {
            return;
        }
    } else if (towerType==TowerType::Bomb){
        towerBoard=120;
        cooldownTime = 1.5f;
        if (!towerTexture.loadFromFile(BOMB_TOWER_ADDRESS)) {
            return;
        }
    }
}

void Tower::render(RenderWindow& window){
    towerSprite.setTexture(towerTexture);
    Vector2u towerTexSize = towerSprite.getTexture()->getSize();
    float towerScaleX = SCALE_TO_TILE / towerTexSize.x;
    float towerScaleY = SCALE_TO_TILE / towerTexSize.y;
    towerSprite.setScale(towerScaleX, towerScaleY);
    towerSprite.setPosition(towerX, towerY);
    window.draw(towerSprite); 

    boundCircle.setRadius(towerBoard);
    boundCircle.setFillColor(TRANSPARENT_CIRCLE_COLOR);  
    //boundCircle.setPosition(towerX - towerBoard + TILE_SIZE/2, towerY - towerBoard + TILE_SIZE/2);
    boundCircle.setOrigin(towerBoard, towerBoard);
    boundCircle.setPosition(towerX + TILE_SIZE/2, towerY + TILE_SIZE/2);
    window.draw(boundCircle);
}

void Tower::tryShoot(vector<Baloon>& baloons) {
    for (auto& baloon : baloons) {
        Vector2f baloonCenter = baloon.getBaloonSprite().getPosition();
        float dx = towerX + TILE_SIZE/2 - baloonCenter.x - baloon.getBaloonSizeX()/2;
        float dy = towerY + TILE_SIZE/2 - baloonCenter.y - baloon.getBaloonSizeY()/2;
        float distance = sqrt(dx*dx + dy*dy);

        if (distance<towerBoard){
            //cout << "Baloon detected in my territory!" << endl;
        }
    }
}
