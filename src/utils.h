#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <memory>
#include <cstdlib>
#include <utility>

using namespace std;
using namespace sf;

const string MAP_FILE_ADDRESS = "files/map.txt";
const string PATH_TILE_ADDRESS = "files/pics/path_tile.png";
const string TOWER_TILE_ADDRESS = "files/pics/tower_tile.png";
const string SIMPLE_BALOON_ADDRESS = "files/pics/simple_baloon.png";
const string PREGNANT_BALOON_ADDRESS = "files/pics/pregnant_baloon.png";
const string BACKGROUND_MUSIC_ADDRESS = "files/audio/pirate-of-caribbean.ogg";
const string FONT_ADDRESS = "files/fonts/Noto_Sans/static/NotoSans-Regular.ttf";
const string BOMB_TOWER_ADDRESS = "files/pics/bomb_tower.png";
const string SIMPLE_TOWER_ADDRESS = "files/pics/simple_tower.png";
const string ICE_TOWER_ADDRESS = "files/pics/ice_tower.png";
const vector<int> TOWER_PRICES = {200, 400, 600};
const int TILE_SIZE = 80;
const float SIMPLE_BALOON_SIZE_X = 40.0f;
const float SIMPLE_BALOON_SIZE_Y = 60.0f;
const float PREGNANT_BALOON_SIZE_X = 60.0f;
const float PREGNANT_BALOON_SIZE_Y = 60.0f;
const float SHOP_ITEM_X = 125.0f;
const float SHOP_ITEM_Y = 150.0f;
const float SCALE_TO_TILE = 80.0f;
const int MENU_X = 1080;
const int MENU_Y = 720;
const Color SCORE_RECT_COLOR = Color(139, 69, 19);
const Color SIDEBR_RECT_COLOR = Color(205, 133, 63);
const Color TRANSPARENT_CIRCLE_COLOR = Color(128, 128, 128, 64);
const string NORMAL = "Normal";
const string PREGNANT = "Pregnant";
const string SHOP = "Shop";
const string ROUND = "Round";
const int BALOON_SPEED = 10;
const int STARTING_SCORE = 300;


enum class Direction {
    Right,
    Down,
    Left,
    Up
};

enum class TowerType {
    Simple,
    Ice,
    Bomb
};

enum class BaloonType {
    Simple,
    Pregnant
};

#endif //UTILS_H