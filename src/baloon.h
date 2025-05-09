#ifndef BALOON_H
#define BALOON_H

#include "utils.h"

class Baloon{
public:
    Baloon(vector<vector<string>> theMap_, vector<pair<int,int>> roadMap_);
    void update();
    void render(RenderWindow& window);
private:
    int baloonX;
    int baloonY;
    int baloonSpeed;
    vector<pair<int,int>> roadMap;
    vector<vector<string>> theMap;
    pair<int,int> tile;
    int tileIndex;
    pair<int, int> deltaTile;
};

#endif //BALOON_H