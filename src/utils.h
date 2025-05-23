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
#include <cmath>

using namespace std;
using namespace sf;

const string MAP_FILE_ADDRESS = "files/map.txt";
const string PATH_TILE_ADDRESS = "files/pics/path_tile.png";
const string TOWER_TILE_ADDRESS = "files/pics/tower_tile.png";
const string SIMPLE_BALOON_ADDRESS = "files/pics/simple_baloon.png";
const string PREGNANT_BALOON_ADDRESS = "files/pics/pregnant_baloon.png";
const string BACKGROUND_MUSIC_ADDRESS = "files/audio/pirate-of-caribbean.ogg";
const string SIMPLE_TOWER_MUSIC_ADDRESS = "files/audio/simple-sound.ogg";
const string ICE_TOWER_MUSIC_ADDRESS = "files/audio/snow-sound.ogg";
const string BOMB_TOWER_MUSIC_ADDRESS = "files/audio/bomb-sound.ogg";
const string EVIL_MUSIC_ADDRESS = "files/audio/evil-sound.ogg";
const string TADA_MUSIC_ADDRESS = "files/audio/tada-sound.ogg";
const string MAIN_FONT_ADDRESS = "files/fonts/Noto_Sans/static/NotoSans-Regular.ttf";
const string END_FONT_ADDRESS = "files/fonts/Anton/Anton-Regular.ttf";
const string BOMB_TOWER_ADDRESS = "files/pics/bomb_tower.png";
const string SIMPLE_TOWER_ADDRESS = "files/pics/simple_tower.png";
const string ICE_TOWER_ADDRESS = "files/pics/ice_tower.png";
const string BOMB_TOWER_BW_ADDRESS = "files/pics/bomb_tower_bw.png";
const string SIMPLE_TOWER_BW_ADDRESS = "files/pics/simple_tower_bw.png";
const string ICE_TOWER_BW_ADDRESS = "files/pics/ice_tower_bw.png";
const vector<int> TOWER_PRICES = {200, 300, 500};
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
const string WON_MESSAGE = "YOU COOKED";
const string LOST_MESSAGE = "YOU WERE COOKED";
const int BALOON_SPEED = 10;
const int BABY_BALOONS = 2;
const int STARTING_SCORE = 300;
const int SIMPLE_KILL_SCORE = 10;
const int PREGNANT_KILL_SCORE = 25;
const int STARTING_MISTAKES = 7;
const int ROUND_NUMBERS = 5;
const float FREEZE_DURATION = 0.9f;
const int SIMPLE_TOWER_BOARD = 180;
const float SIMPLE_TOWER_COOLDOWN_TIME = 1.5f; 
const int ICE_TOWER_BOARD = 150;
const float ICE_TOWER_COOLDOWN_TIME = 1.0f; 
const int BOMB_TOWER_BOARD = 120;
const float BOMB_TOWER_COOLDOWN_TIME = 2.5f; 
const float BOMB_BLAST_RADIUS = 80.0f;
const Vector2f SHOP_SIMPLE_TOWER_POS = {920, 150};
const Vector2f SHOP_ICE_TOWER_POS = {920, 340};
const Vector2f SHOP_BOMB_TOWER_POS = {920, 530};
const Vector2f SHOP_SIMPLE_TEXT_POS = {960, 290};
const Vector2f SHOP_ICE_TEXT_POS = {960, 484};
const Vector2f SHOP_BOMB_TEXT_POS = {960, 672};
const Vector2f SHOP_TEXT_POS = {928, 90};
const Vector2f SCORE_TEXT_POS = {42, 20};
const Vector2f REMAINING_TEXT_POS = {970, 20};

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

enum class GameResult {
    Won,
    Lost
};

#endif //UTILS_H