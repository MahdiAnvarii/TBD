#include "system.h"
#include "utils.h"
#include "map.h"

System::System()
    : window(VideoMode(MENU_X, MENU_Y), "Tower Balloon Defense") {
    window.setFramerateLimit(144);
    setBaloons();
    run();
}

void System::setBaloons(){
    vector<pair<int,int>> roadMap = map.getRoadMap();
    vector<vector<string>> theMap = map.getTheMap();
    for (int i=0; i<1; ++i){
        Baloon baloon(theMap, roadMap);
        baloons.push_back(baloon);
    }
}

void System::run(){
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        update();
        render();
    }
}

void System::update(){
    for (int i=0; i<1; ++i){
        baloons[i].update();
    }   
}

void System::render(){
    window.clear();
    map.render(window);
    for (int i=0; i<1; ++i){
        baloons[i].render(window);
    }
    window.display();
}