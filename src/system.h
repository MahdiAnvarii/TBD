#ifndef SYSTEM_H
#define SYSTEM_H

#include "utils.h"
#include "map.h"
#include "baloon.h"
#include "shop.h"
#include "tower.h"
#include "wave_configs.h"

class System{
public:
    System();
    void setBaloons();
    void playMusic();
    void run();
    void update();
    void render();
    void renderTexts();
    void handleMouseClick(int mouseX, int mouseY);
    RenderWindow window;
private:
    int score;
    int round;
    Map map;
    vector<Baloon> baloons;
    Shop shop;
    bool isPlacingTower = false;
    vector<Tower> towers;
    vector<vector<string>> theMap;
    vector<pair<int,int>> filledTiles;
    TowerType towerType;
    int towerPrice;
    unique_ptr<WaveManager> waveManager;
    //Music music;
};

#endif //SYSTEM_H