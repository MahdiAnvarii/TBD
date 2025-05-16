#ifndef BALOON_H
#define BALOON_H

#include "utils.h"

class Baloon{
public:
    Baloon(const vector<vector<string>>& theMap_, const vector<pair<int,int>>& roadMap_, BaloonType baloonType_);
    void setBaloonType();
    void setBabyBaloon(Vector2f parentPosition, pair<int,int> tile_, int tileIndex_, pair<int, int> deltaTile_);
    void update();
    void render(RenderWindow& window);
    Sprite getBaloonSprite() const;
    float getBaloonSizeX() const;
    float getBaloonSizeY() const;
    BaloonType getBaloonType() const;
    pair<int,int> getBaloonTile() const;
    pair<int, int> getBaloonDeltaTile() const;
    int getBaloonTileIndex() const;
    void markAsDead();
    bool dead() const;
    void markAsFrozen();
    bool frozen() const;
    bool didYouRunAway() const;
private:
    int baloonX;
    int baloonY;
    int baloonSpeed;
    float baloonSizeX;
    float baloonSizeY;
    BaloonType baloonType;
    vector<pair<int,int>> roadMap;
    vector<vector<string>> theMap;
    pair<int,int> tile;
    int tileIndex;
    pair<int, int> deltaTile;
    Texture baloonTexture;
    Sprite baloonSprite;
    bool isDead = false;
    bool isFrozen = false;
    Clock freezeClock;
    float freezeDuration = FREEZE_DURATION;
    bool reachFinalTile = false;
    bool runAway = false;
};

#endif //BALOON_H