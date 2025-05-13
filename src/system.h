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
    void endGame();
    void renderEndTexts();
    RenderWindow window;
private:
    int score;
    int remainingMistakes;
    int round;
    shared_ptr<Map> map;
    vector<shared_ptr<Baloon>> baloons;
    vector<shared_ptr<Baloon>> newBornBaloons;
    shared_ptr<Shop> shop;
    bool isPlacingTower = false;
    vector<shared_ptr<Tower>> towers;
    vector<vector<string>> theMap;
    vector<pair<int,int>> filledTiles;
    TowerType towerType;
    int towerPrice;
    shared_ptr<WaveManager> waveManager;
    GameResult gameResult;
    Music music;
    Music finalMusic;
};

#endif //SYSTEM_H