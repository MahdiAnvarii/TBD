#ifndef MAP_H
#define MAP_H

#include "utils.h"

class Map{
public:
    Map();
    void readMapFile();
    void specifyStartingPoint();
    Direction specifyStartingDir();
    void render(RenderWindow& window);
    void renderRects(RenderWindow& window);
    void findRoadMap(pair<int,int> tile, Direction dir);
    vector<vector<string>> getTheMap() const;
    pair<int,int> getStartingPoint() const;
    vector<pair<int,int>> getRoadMap() const;
private:
    vector<vector<string>> theMap;
    pair<int,int> startingPoint;
    vector<pair<int,int>> roadMap;
};

#endif //MAP_H