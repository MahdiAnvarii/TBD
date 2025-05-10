#ifndef SHOP_H
#define SHOP_H

#include "utils.h"

class Shop{
public:
    Shop();
    void render(RenderWindow& window);
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
    Sprite simpleTowerSprite;
    Sprite iceTowerSprite;
    Sprite bombTowerSprite;
};

#endif //SHOP_H