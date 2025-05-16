#include "system.h"
#include "utils.h"
#include "baloon.h"
#include "map.h"
#include "shop.h"
#include "tower.h"
#include "wave_configs.h"

System::System()
    : map(make_shared<Map>()),
        shop(make_shared<Shop>()),
        window(VideoMode(MENU_X, MENU_Y), "Tower Balloon Defense") {
    window.setFramerateLimit(144);
    score = STARTING_SCORE;
    remainingMistakes = STARTING_MISTAKES;
    theMap = map->getTheMap();
    waveManager = make_shared<WaveManager>(map, baloons);
    playMusic();
    run();
}

void System::playMusic(){
    if (!music.openFromFile(BACKGROUND_MUSIC_ADDRESS)) {
        cerr << "Error loading music file!" << endl;
        return;
    }
    music.setLoop(true); 
    music.play();
}

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

        if (remainingMistakes<=0){
            gameResult = GameResult::Lost;
            music.stop();
            finalMusic.openFromFile(EVIL_MUSIC_ADDRESS);
            endGame();
            break;
        }
        if (baloons.empty() && round==ROUND_NUMBERS && waveManager->getSpawnClock() > WAVE_LEAST_TIME_TO_WIN){
            gameResult = GameResult::Won;
            music.stop();
            finalMusic.openFromFile(TADA_MUSIC_ADDRESS);
            endGame();
            break;
        }
    }
    exit(0);
}

void System::update(){
    waveManager->update();
    round = waveManager->getRoundOfWave();
    for (auto& baloon : baloons){
        baloon->update();
    }   
    for (auto& tower : towers){
        tower->tryShoot(baloons);
    }

    baloons.erase(
    remove_if(baloons.begin(), baloons.end(), [this](const shared_ptr<Baloon>& b) {
        if (b->dead()) {
            if (b->getBaloonType() == BaloonType::Simple)
                score += SIMPLE_KILL_SCORE;
            else if (b->getBaloonType() == BaloonType::Pregnant){
                score += PREGNANT_KILL_SCORE;
                for (int i=0; i<BABY_BALOONS; i++){
                    shared_ptr<Baloon> babyBaloon = make_shared<Baloon>(theMap, map->getRoadMap(), BaloonType::Simple);
                    babyBaloon->setBabyBaloon(b->getBaloonSprite().getPosition(), b->getBaloonTile(), b->getBaloonTileIndex(), b->getBaloonDeltaTile());
                    newBornBaloons.push_back(babyBaloon);
                }
            }
            return true;
        }
        return false;
    }), baloons.end());
    baloons.insert(baloons.end(), newBornBaloons.begin(), newBornBaloons.end());
    newBornBaloons.clear();

    baloons.erase(
    remove_if(baloons.begin(), baloons.end(), [this](const shared_ptr<Baloon>& b) {
        if (b->didYouRunAway()) {
            remainingMistakes--;
            return true;
        }
        return false;
    }), baloons.end());
}

void System::render(){
    window.clear();
    map->render(window);
    for (auto& baloon : baloons){
        baloon->render(window);
    }
    for (auto& tower : towers){
        tower->render(window);
    }
    map->renderRects(window);
    renderTexts();
    shop->render(window, score);
    window.display();
}

void System::renderTexts(){
    Font font;
    if (!font.loadFromFile(MAIN_FONT_ADDRESS)) {
        return;
    }
    Text shopText;
    shopText.setFont(font);
    shopText.setString(SHOP);
    shopText.setCharacterSize(44);
    shopText.setFillColor(Color::White);
    shopText.setPosition(SHOP_TEXT_POS);
    window.draw(shopText);

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setString(to_string(score));
    scoreText.setCharacterSize(38);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(SCORE_TEXT_POS);
    window.draw(scoreText);

    Text remainingText;
    remainingText.setFont(font);
    remainingText.setString(to_string(remainingMistakes));
    remainingText.setCharacterSize(38);
    remainingText.setFillColor(Color::White);
    remainingText.setPosition(REMAINING_TEXT_POS);
    window.draw(remainingText);

    Text roundText;
    roundText.setFont(font);
    roundText.setString(ROUND + " " + to_string(round));
    roundText.setCharacterSize(60);
    roundText.setFillColor(Color::White);
    FloatRect roundTextBounds = roundText.getGlobalBounds();
    roundText.setPosition((MENU_X-roundTextBounds.width)/2, 0);
    window.draw(roundText);
}

void System::endGame(){
    finalMusic.play();
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        renderEndTexts();
    }
}

void System::renderEndTexts(){
    window.clear();
    Font font;
    if (!font.loadFromFile(END_FONT_ADDRESS)) {
        return;
    }
    Text endText;
    endText.setFont(font);
    endText.setString(gameResult==GameResult::Won ? WON_MESSAGE : LOST_MESSAGE);
    endText.setCharacterSize(70);
    endText.setFillColor(Color::White);
    FloatRect endTextBounds = endText.getGlobalBounds();
    endText.setPosition((MENU_X-endTextBounds.width)/2, 165);
    window.draw(endText);
    window.display();
}

void System::handleMouseClick(int mouseX, int mouseY) {
    Vector2f clickPos(mouseX, mouseY);

    if (shop->getSimpleTowerSprite().getGlobalBounds().contains(clickPos)) {
        towerType = TowerType::Simple;
        towerPrice = shop->getSimpleTowerPrice();
        if (score>=towerPrice) isPlacingTower = true;
        return;
    } else if (shop->getIceTowerSprite().getGlobalBounds().contains(clickPos)) {
        towerType = TowerType::Ice;
        towerPrice = shop->getIceTowerPrice();
        if (score>=towerPrice) isPlacingTower = true;
        return;
    } else if (shop->getBombTowerSprite().getGlobalBounds().contains(clickPos)) {
        towerType = TowerType::Bomb;
        towerPrice = shop->getBombTowerPrice();
        if (score>=towerPrice) isPlacingTower = true;
        return;
    }

    if (isPlacingTower) {        
        int col = mouseX / TILE_SIZE;
        int row = (mouseY - TILE_SIZE) / TILE_SIZE;
        if (row >= 0 && row < theMap.size() &&
            col >= 0 && col < theMap[0].size() &&
            theMap[row][col] == "-" && find(filledTiles.begin(), filledTiles.end(), make_pair(row,col)) == filledTiles.end()) {
                shared_ptr<Tower> tower = make_shared<Tower>(row, col, towerPrice, towerType);
                towers.push_back(tower);
                filledTiles.push_back(make_pair(row,col));
                score-=towerPrice;
                isPlacingTower = false;
        }
    }
}