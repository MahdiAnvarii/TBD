#ifndef SYSTEM_H
#define SYSTEM_H

#include "utils.h"
#include "map.h"
#include "baloon.h"

class System{
public:
    System();
    void setBaloons();
    void run();
    void update();
    void render();
    RenderWindow window;
private:
    Map map;
    vector<Baloon> baloons;
};

#endif //SYSTEM_H