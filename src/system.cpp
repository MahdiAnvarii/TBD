#include "system.h"
#include "utils.h"
#include "baloon.h"
#include "map.h"
#include "shop.h"
#include "tower.h"
#include "wave_configs.h"

System::System()
    : window(VideoMode(MENU_X, MENU_Y), "Tower Balloon Defense") {
    window.setFramerateLimit(144);
    score = STARTING_SCORE;
    theMap = map.getTheMap();
    waveManager = make_unique<WaveManager>(map, baloons);
    //setBaloons();
    //playMusic();
    run();
}

void System::setBaloons(){
    vector<pair<int,int>> roadMap = map.getRoadMap();
    for (int i=0; i<1; ++i){
        Baloon baloon(theMap, roadMap, BaloonType::Pregnant);
        baloons.push_back(baloon);
    }
}

/*
void System::playMusic(){
    if (!music.openFromFile(BACKGROUND_MUSIC_ADDRESS)) {
        cerr << "Error loading music file!" << endl;
        return;
    }
    music.setLoop(true); 
    music.play();
}
*/

void System::run(){
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
                handleMouseClick(event.mouseButton.x, event.mouseButton.y);
        }
        update();
        render();
    }
    exit(0);
}

void System::update(){
    waveManager->update();
    round = waveManager->getRoundOfWave();
    for (auto& baloon : baloons){
        baloon.update();
    }   
    for (auto& tower : towers){
        tower.tryShoot(baloons);
    }
}

void System::render(){
    window.clear();
    map.render(window);
    for (auto& baloon : baloons){
        baloon.render(window);
    }
    for (auto& tower : towers){
        tower.render(window);
    }
    map.renderRects(window);
    renderTexts();
    shop.render(window);
    window.display();
}

void System::renderTexts(){
    Font font;
    if (!font.loadFromFile(FONT_ADDRESS)) {
        return;
    }
    Text shopText;
    shopText.setFont(font);
    shopText.setString(SHOP);
    shopText.setCharacterSize(44);
    shopText.setFillColor(Color::White);
    shopText.setPosition(928, 90);
    window.draw(shopText);

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setString(to_string(score));
    scoreText.setCharacterSize(38);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(42, 20);
    window.draw(scoreText);

    Text roundText;
    roundText.setFont(font);
    roundText.setString(ROUND + " " + to_string(round));
    roundText.setCharacterSize(60);
    roundText.setFillColor(Color::White);
    roundText.setPosition(425, 0);
    window.draw(roundText);
}

void System::handleMouseClick(int mouseX, int mouseY) {
    Vector2f clickPos(mouseX, mouseY);

    if (shop.getSimpleTowerSprite().getGlobalBounds().contains(clickPos)) {
        isPlacingTower = true;
        towerType = TowerType::Simple;
        towerPrice = shop.getSimpleTowerPrice();
        return;
    } else if (shop.getIceTowerSprite().getGlobalBounds().contains(clickPos)) {
        isPlacingTower = true;
        towerType = TowerType::Ice;
        towerPrice = shop.getIceTowerPrice();
        return;
    } else if (shop.getBombTowerSprite().getGlobalBounds().contains(clickPos)) {
        isPlacingTower = true;
        towerType = TowerType::Bomb;
        towerPrice = shop.getBombTowerPrice();
        return;
    }

    if (isPlacingTower) {        
        int col = mouseX / TILE_SIZE;
        int row = (mouseY - TILE_SIZE) / TILE_SIZE;
        if (row >= 0 && row < theMap.size() &&
            col >= 0 && col < theMap[0].size() &&
            theMap[row][col] == "-" && find(filledTiles.begin(), filledTiles.end(), make_pair(row,col)) == filledTiles.end()) {
                Tower tower(row, col, towerPrice, towerType);
                towers.push_back(tower);
                filledTiles.push_back(make_pair(row,col));
                isPlacingTower = false;
        }
    }
}