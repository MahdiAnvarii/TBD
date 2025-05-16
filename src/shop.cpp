#include "shop.h"
#include "utils.h"

Shop::Shop(){
    simplePrice = TOWER_PRICES[0];
    icePrice = TOWER_PRICES[1];
    bombPrice = TOWER_PRICES[2];
}

void Shop::render(RenderWindow& window, int score){
    if (!simpleTowerTexture.loadFromFile(SIMPLE_TOWER_ADDRESS) || !simpleTowerTextureBW.loadFromFile(SIMPLE_TOWER_BW_ADDRESS)) {
        return;
    }
    simpleTowerSprite.setTexture(score >= simplePrice ? simpleTowerTexture : simpleTowerTextureBW);
    Vector2u simpleTowerTexSize = simpleTowerSprite.getTexture()->getSize();
    float simpleTowerScaleX = SHOP_ITEM_X / simpleTowerTexSize.x;
    float simpleTowerScaleY = SHOP_ITEM_Y / simpleTowerTexSize.y;
    simpleTowerSprite.setScale(simpleTowerScaleX, simpleTowerScaleY);
    simpleTowerSprite.setPosition(SHOP_SIMPLE_TOWER_POS);
    window.draw(simpleTowerSprite); 

    if (!iceTowerTexture.loadFromFile(ICE_TOWER_ADDRESS) || !iceTowerTextureBW.loadFromFile(ICE_TOWER_BW_ADDRESS)) {
        return;
    }
    iceTowerSprite.setTexture(score >= icePrice ? iceTowerTexture : iceTowerTextureBW);
    Vector2u iceTowerTexSize = iceTowerSprite.getTexture()->getSize();
    float iceTowerScaleX = SHOP_ITEM_X / iceTowerTexSize.x;
    float iceTowerScaleY = SHOP_ITEM_Y / iceTowerTexSize.y;
    iceTowerSprite.setScale(iceTowerScaleX, iceTowerScaleY);
    iceTowerSprite.setPosition(SHOP_ICE_TOWER_POS);
    window.draw(iceTowerSprite); 

    if (!bombTowerTexture.loadFromFile(BOMB_TOWER_ADDRESS) || !bombTowerTextureBW.loadFromFile(BOMB_TOWER_BW_ADDRESS)) {
        return;
    }
    bombTowerSprite.setTexture(score >= bombPrice ? bombTowerTexture : bombTowerTextureBW);
    Vector2u bombTowerTexSize = bombTowerSprite.getTexture()->getSize();
    float bombTowerScaleX = SHOP_ITEM_X / bombTowerTexSize.x;
    float bombTowerScaleY = SHOP_ITEM_Y / bombTowerTexSize.y;
    bombTowerSprite.setScale(bombTowerScaleX, bombTowerScaleY);
    bombTowerSprite.setPosition(SHOP_BOMB_TOWER_POS);
    window.draw(bombTowerSprite); 

    renderPrices(window);
}

void Shop::renderPrices(RenderWindow& window){
    Font font;
    if (!font.loadFromFile(MAIN_FONT_ADDRESS)) {
        return;
    }
    Text simpleText;
    simpleText.setFont(font);
    simpleText.setString(to_string(simplePrice));
    simpleText.setCharacterSize(26);
    simpleText.setFillColor(Color::Black);
    simpleText.setPosition(SHOP_SIMPLE_TEXT_POS);
    window.draw(simpleText);

    Text iceText;
    iceText.setFont(font);
    iceText.setString(to_string(icePrice));
    iceText.setCharacterSize(26);
    iceText.setFillColor(Color::Black);
    iceText.setPosition(SHOP_ICE_TEXT_POS);
    window.draw(iceText);

    Text bombText;
    bombText.setFont(font);
    bombText.setString(to_string(bombPrice));
    bombText.setCharacterSize(26);
    bombText.setFillColor(Color::Black);
    bombText.setPosition(SHOP_BOMB_TEXT_POS);
    window.draw(bombText);
}

Sprite Shop::getSimpleTowerSprite() const { return simpleTowerSprite; }
Sprite Shop::getIceTowerSprite() const { return iceTowerSprite; }
Sprite Shop::getBombTowerSprite() const { return bombTowerSprite; }
int Shop::getSimpleTowerPrice() const { return simplePrice; }
int Shop::getIceTowerPrice() const { return icePrice; };
int Shop::getBombTowerPrice() const { return bombPrice; }