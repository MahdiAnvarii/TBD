#ifndef TOWER_H
#define TOWER_H

#include "utils.h"
#include "baloon.h"

class Tower{
public:
    Tower(int row_, int col_, int towerPrice_, TowerType towerType_);
    void setTowerType();
    void render(RenderWindow& window);
    void tryShoot(vector<Baloon>& baloons);
private:
    int row;
    int col;
    int towerPrice;
    int towerX;
    int towerY;
    int towerBoard;
    Texture towerTexture;
    Sprite towerSprite;
    TowerType towerType;
    CircleShape boundCircle;
    Clock shootCooldown;
    float cooldownTime;
};

#endif //TOWER_H