#ifndef BALOON_H
#define BALOON_H

#include "utils.h"

class Baloon{
public:
    Baloon(vector<vector<string>> theMap_, vector<pair<int,int>> roadMap_, BaloonType baloonType_);
    void setBaloonType();
    void update();
    void render(RenderWindow& window);
    Sprite getBaloonSprite() const;
    float getBaloonSizeX() const;
    float getBaloonSizeY() const;
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
};

#endif //BALOON_H