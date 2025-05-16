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
        towerBoard = SIMPLE_TOWER_BOARD;
        cooldownTime = SIMPLE_TOWER_COOLDOWN_TIME;
        if (!towerTexture.loadFromFile(SIMPLE_TOWER_ADDRESS) || !shotBuffer.loadFromFile(SIMPLE_TOWER_MUSIC_ADDRESS)) {
            return;
        }
        shotSound.setBuffer(shotBuffer);
    } else if (towerType==TowerType::Ice){
        towerBoard = ICE_TOWER_BOARD;
        cooldownTime = ICE_TOWER_COOLDOWN_TIME;
        if (!towerTexture.loadFromFile(ICE_TOWER_ADDRESS) || !shotBuffer.loadFromFile(ICE_TOWER_MUSIC_ADDRESS)) {
            return;
        }
        shotSound.setBuffer(shotBuffer);
    } else if (towerType==TowerType::Bomb){
        towerBoard = BOMB_TOWER_BOARD;
        cooldownTime = BOMB_TOWER_COOLDOWN_TIME;
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

float Tower::distanceToTowerCenter(const shared_ptr<Baloon>& baloon) {
    Vector2f baloonCenter = baloon->getBaloonSprite().getPosition();
    float dx = towerX + TILE_SIZE/2 - baloonCenter.x - baloon->getBaloonSizeX()/2;
    float dy = towerY + TILE_SIZE/2 - baloonCenter.y - baloon->getBaloonSizeY()/2;
    return std::sqrt(dx*dx + dy*dy);
}

bool Tower::isInTowerRange(const shared_ptr<Baloon>& baloon) {
    return distanceToTowerCenter(baloon) <= towerBoard;
}

void Tower::tryShoot(vector<shared_ptr<Baloon>>& baloons) {
    if (shootCooldown.getElapsedTime().asSeconds() < cooldownTime)
        return;

    shared_ptr<Baloon> target = nullptr;

    if (towerType == TowerType::Simple) {
        float minDistance = INFINITY;
        for (auto& baloon : baloons) {
            if (baloon->dead()) continue;
            float dist = distanceToTowerCenter(baloon);
            if (dist < towerBoard && dist < minDistance) {
                minDistance = dist;
                target = baloon;
            }
        }
        if (target) {
            target->markAsDead();
            shotSound.setVolume(70.f);
            shotSound.play();
            shootCooldown.restart();
        }

    } else if (towerType == TowerType::Ice) {
        float minDistance = INFINITY;
        for (auto& baloon : baloons) {
            if (baloon->dead() || baloon->frozen()) continue;
            float dist = distanceToTowerCenter(baloon);
            if (dist < towerBoard && dist < minDistance) {
                minDistance = dist;
                target = baloon;
            }
        }
        if (target) {
            target->markAsFrozen();
            shotSound.setVolume(100.f);
            shotSound.play();
            shootCooldown.restart();
        }

    } else if (towerType == TowerType::Bomb) {
        int maxNeighbors = 0;
        for (auto& baloon : baloons) {
            if (baloon->dead()) continue;
            if (!isInTowerRange(baloon)) continue;

            int neighbors = countNearbyBaloons(baloon, baloons);
            if (neighbors > maxNeighbors) {
                maxNeighbors = neighbors;
                target = baloon;
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

bool Tower::isWithinBlastRadius(const shared_ptr<Baloon>& target, const shared_ptr<Baloon>& other) {
    Vector2f targetCenter = target->getBaloonSprite().getPosition();
    Vector2f otherCenter = other->getBaloonSprite().getPosition();

    float dx = targetCenter.x + target->getBaloonSizeX()/2 - otherCenter.x - other->getBaloonSizeX()/2;
    float dy = targetCenter.y + target->getBaloonSizeY()/2 - otherCenter.y - other->getBaloonSizeY()/2;

    float distance = sqrt(dx*dx + dy*dy);
    return distance <= bombBlastRadius;
}

int Tower::countNearbyBaloons(const shared_ptr<Baloon>& target, const vector<shared_ptr<Baloon>>& baloons) {
    int count = 0;
    for (const auto& baloon : baloons) {
        if (isWithinBlastRadius(target, baloon)) {
            count++;
        }
    }
    return count;
}

void Tower::killNearbyBaloons(shared_ptr<Baloon>& target, vector<shared_ptr<Baloon>>& baloons) {
    for (auto& baloon : baloons) {
        if (isWithinBlastRadius(target, baloon)) {
            baloon->markAsDead();
        }
    }
    target->markAsDead();
}

