#include "tower.h"
#include "utils.h"
#include "baloon.h"

Tower::Tower(int row_, int col_, int towerPrice_, TowerType towerType_){
    row = row_;
    col = col_;
    towerPrice = towerPrice_;
    towerType = towerType_;
    towerX = col * TILE_SIZE;
    towerY = (row + 1) * TILE_SIZE;
    setTowerType();
}

void Tower::setTowerType(){
    if (towerType==TowerType::Simple){
        towerBoard=180;
        cooldownTime = 1.5f;
        if (!towerTexture.loadFromFile(SIMPLE_TOWER_ADDRESS) || !shotBuffer.loadFromFile(SIMPLE_TOWER_MUSIC_ADDRESS)) {
            return;
        }
        shotSound.setBuffer(shotBuffer);
    } else if (towerType==TowerType::Ice){
        towerBoard=150;
        cooldownTime = 1.2f;
        if (!towerTexture.loadFromFile(ICE_TOWER_ADDRESS) || !shotBuffer.loadFromFile(ICE_TOWER_MUSIC_ADDRESS)) {
            return;
        }
        shotSound.setBuffer(shotBuffer);
    } else if (towerType==TowerType::Bomb){
        towerBoard=120;
        cooldownTime = 3.0f;
        if (!towerTexture.loadFromFile(BOMB_TOWER_ADDRESS) || !shotBuffer.loadFromFile(BOMB_TOWER_MUSIC_ADDRESS)) {
            return;
        }
        shotSound.setBuffer(shotBuffer);
    }
}

void Tower::render(RenderWindow& window){
    towerSprite.setTexture(towerTexture);
    Vector2u towerTexSize = towerSprite.getTexture()->getSize();
    float towerScaleX = SCALE_TO_TILE / towerTexSize.x;
    float towerScaleY = SCALE_TO_TILE / towerTexSize.y;
    towerSprite.setScale(towerScaleX, towerScaleY);
    towerSprite.setPosition(towerX, towerY);
    window.draw(towerSprite); 

    boundCircle.setRadius(towerBoard);
    boundCircle.setFillColor(TRANSPARENT_CIRCLE_COLOR);  
    boundCircle.setOrigin(towerBoard, towerBoard);
    boundCircle.setPosition(towerX + TILE_SIZE/2, towerY + TILE_SIZE/2);
    window.draw(boundCircle);
}

void Tower::tryShoot(vector<shared_ptr<Baloon>>& baloons) {
    if (shootCooldown.getElapsedTime().asSeconds() < cooldownTime)
        return;

    shared_ptr<Baloon> target = nullptr;
    if (towerType==TowerType::Simple) {
        float minDistance = INFINITY;
        for (auto& baloon : baloons) {
            if (baloon->dead()) continue;

            Vector2f baloonCenter = baloon->getBaloonSprite().getPosition();
            float dx = towerX + TILE_SIZE/2 - baloonCenter.x - baloon->getBaloonSizeX()/2;
            float dy = towerY + TILE_SIZE/2 - baloonCenter.y - baloon->getBaloonSizeY()/2;
            float distance = sqrt(dx*dx + dy*dy);
            if (distance < towerBoard && distance < minDistance) {
                minDistance = distance;
                target = baloon;
            }
        }
        if (target) {
            target->markAsDead();
            shotSound.setVolume(70.f);
            shotSound.play();
            shootCooldown.restart();
        }

    } else if ((towerType==TowerType::Ice)){
        float minDistance = INFINITY;
        for (auto& baloon : baloons) {
            if (baloon->dead()) continue;
            if (baloon->frozen()) continue;

            Vector2f baloonCenter = baloon->getBaloonSprite().getPosition();
            float dx = towerX + TILE_SIZE/2 - baloonCenter.x - baloon->getBaloonSizeX()/2;
            float dy = towerY + TILE_SIZE/2 - baloonCenter.y - baloon->getBaloonSizeY()/2;
            float distance = sqrt(dx*dx + dy*dy);
            if (distance < towerBoard && distance < minDistance) {
                minDistance = distance;
                target = baloon;
            }
        }
        if (target) {
            target->markAsFrozen();
            shotSound.setVolume(100.f);
            shotSound.play();
            shootCooldown.restart();
        }
    }
    else if ((towerType==TowerType::Bomb)){
        int maxNeighbors = 0;
        for (auto& baloon : baloons) {
            if (baloon->dead()) continue;

            Vector2f baloonCenter = baloon->getBaloonSprite().getPosition();
            float dx = towerX + TILE_SIZE/2 - baloonCenter.x - baloon->getBaloonSizeX()/2;
            float dy = towerY + TILE_SIZE/2 - baloonCenter.y - baloon->getBaloonSizeY()/2;
            float distance = sqrt(dx*dx + dy*dy);
            if (distance > towerBoard) continue;

            int neighbors = countNearbyBaloons(baloon, baloons);
            if (neighbors > maxNeighbors) {
                maxNeighbors = neighbors;
                target = baloon;;
            }
        }
        if (target) {
            killNearbyBaloons(target, baloons);
            shotSound.setVolume(100.f);
            shotSound.play();
            shootCooldown.restart();
        }
    }
} 

int Tower::countNearbyBaloons(const shared_ptr<Baloon>& target, const vector<shared_ptr<Baloon>>& baloons) {
    int count = 0;
    Vector2f targetCenter = target->getBaloonSprite().getPosition();
    for (const auto& baloon : baloons) {
        Vector2f baloonCenter = baloon->getBaloonSprite().getPosition();
        float dx = targetCenter.x + target->getBaloonSizeX()/2 - baloonCenter.x - baloon->getBaloonSizeX()/2;
        float dy = targetCenter.y + target->getBaloonSizeY()/2 - baloonCenter.y - baloon->getBaloonSizeY()/2;
        float distance = sqrt(dx*dx + dy*dy);
        if (distance <= bombBlastRadius)
            count++;
    }
    return count;
}

void Tower::killNearbyBaloons(shared_ptr<Baloon>& target, vector<shared_ptr<Baloon>>& baloons) {
    Vector2f targetCenter = target->getBaloonSprite().getPosition();
    for (auto& baloon : baloons) {
        Vector2f baloonCenter = baloon->getBaloonSprite().getPosition();
        float dx = targetCenter.x + target->getBaloonSizeX()/2 - baloonCenter.x - baloon->getBaloonSizeX()/2;
        float dy = targetCenter.y + target->getBaloonSizeY()/2 - baloonCenter.y - baloon->getBaloonSizeY()/2;
        float distance = sqrt(dx*dx + dy*dy);
        if (distance <= bombBlastRadius)
            baloon->markAsDead();
    }
    target->markAsDead();
}
