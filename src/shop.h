#ifndef SHOP_H
#define SHOP_H

#include "utils.h"

class Shop{
public:
    Shop();
    void render(RenderWindow& window, int score);
    void renderPrices(RenderWindow& window);
    Sprite getSimpleTowerSprite() const;
    Sprite getIceTowerSprite() const;
    Sprite getBombTowerSprite() const;
    int getSimpleTowerPrice() const;
    int getIceTowerPrice() const;
    int getBombTowerPrice() const;
private:
    int simplePrice;
    int icePrice;
    int bombPrice;
    Texture simpleTowerTexture;
    Texture iceTowerTexture;
    Texture bombTowerTexture;
    Texture simpleTowerTextureBW;
    Texture iceTowerTextureBW;
    Texture bombTowerTextureBW;
    Sprite simpleTowerSprite;
    Sprite iceTowerSprite;
    Sprite bombTowerSprite;
};

#endif //SHOP_H