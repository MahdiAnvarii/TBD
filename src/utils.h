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

using namespace std;
using namespace sf;

const string MAP_FILE_ADDRESS = "files/map.txt";
const string PATH_TILE_ADDRESS = "files/pics/path_tile.png";
const string TOWER_TILE_ADDRESS = "files/pics/tower_tile.png";
const string SIMPLE_BALOON_ADDRESS = "files/pics/simple_baloon.png";
const int TILE_SIZE = 80;
const float BALOON_SIZE_X = 40.0f;
const float BALOON_SIZE_Y = 60.0f;
const int MENU_X = 1080;
const int MENU_Y = 720;
const Color SCORE_RECT_COLOR = Color(250,250,250);
const Color SIDEBR_RECT_COLOR = Color(250,250,250);

enum class Direction {
    Right,
    Down,
    Left,
    Up
};

#endif //UTILS_H