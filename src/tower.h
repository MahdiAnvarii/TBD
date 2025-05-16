#ifndef TOWER_H
#define TOWER_H

#include "utils.h"
#include "baloon.h"

class Tower{
public:
    Tower(int row_, int col_, int towerPrice_, TowerType towerType_);
    void setTowerType();
    void render(RenderWindow& window);
    void tryShoot(vector<shared_ptr<Baloon>>& baloons);
    int countNearbyBaloons(const shared_ptr<Baloon>& target, const vector<shared_ptr<Baloon>>& baloons);
    void killNearbyBaloons(shared_ptr<Baloon>& target, vector<shared_ptr<Baloon>>& baloons);
    bool isWithinBlastRadius(const shared_ptr<Baloon>& target, const shared_ptr<Baloon>& other);
    float distanceToTowerCenter(const shared_ptr<Baloon>& baloon);
    bool isInTowerRange(const shared_ptr<Baloon>& baloon);
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
    float bombBlastRadius = BOMB_BLAST_RADIUS;
    SoundBuffer shotBuffer;
    Sound shotSound;
};

#endif //TOWER_H