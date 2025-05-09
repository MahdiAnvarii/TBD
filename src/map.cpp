#include "map.h"
#include "utils.h"

Map::Map(){
    readMapFile();
    specifyStartingPoint();
    Direction startingDir = specifyStartingDir();
    findRoadMap(startingPoint, startingDir);
}

void Map::readMapFile(){
    ifstream mapFile(MAP_FILE_ADDRESS);
    vector<vector<string>> theMap_;
    vector<string> theMapEachLine;
    string mapFileLine;
    while(getline(mapFile, mapFileLine)){
        theMapEachLine.clear();
        mapFileLine.erase(remove(mapFileLine.begin(), mapFileLine.end(), '\r'), mapFileLine.end());
        mapFileLine.erase(remove(mapFileLine.begin(), mapFileLine.end(), ' '), mapFileLine.end());
        for (const auto tile : mapFileLine){
            theMapEachLine.push_back(string(1, tile));
        }
        theMap_.push_back(theMapEachLine);
    }
    theMap = theMap_;
} 

void Map::specifyStartingPoint(){
    for (int y=0; y < theMap.size(); ++y) {
        for (int x =0; x < theMap[y].size(); ++x) {
            if (theMap[y][x] == "S")
                startingPoint = make_pair(y, x);
        }
    }
}

Direction Map::specifyStartingDir() {
    if (startingPoint.first == 0) return Direction::Down;
    else if (startingPoint.second == 0) return Direction::Right;
    else if (startingPoint.first == theMap.size() - 1) return Direction::Up;
    else return Direction::Left;
}

void Map::findRoadMap(pair<int,int> tile, Direction dir){
    roadMap.push_back(tile);
    if (tile.first>=theMap.size() || tile.first<0 || tile.second>=theMap[0].size() || tile.second<0) return;
    if (theMap[tile.first][tile.second] == "F") return;
    
    if (dir == Direction::Right){
        if ((theMap[tile.first+1][tile.second] == "O") || (theMap[tile.first+1][tile.second] == "F")){
            tile.first+=1;
        } else if ((theMap[tile.first][tile.second+1] == "O") || (theMap[tile.first][tile.second+1] == "F")){
            dir=Direction::Down;
            tile.second+=1;
        } else if ((theMap[tile.first][tile.second-1] == "O") || (theMap[tile.first][tile.second-1] == "F")){
            dir=Direction::Up;
            tile.second-=1;
        }

    } else if (dir == Direction::Down){
        if ((theMap[tile.first][tile.second+1] == "O") || (theMap[tile.first][tile.second+1] == "F")){
            tile.second+=1;
        } else if ((theMap[tile.first+1][tile.second] == "O") || (theMap[tile.first+1][tile.second] == "F")){
            dir=Direction::Right;
            tile.first+=1;
        } else if ((theMap[tile.first-1][tile.second] == "O") || (theMap[tile.first-1][tile.second] == "F")){
            dir=Direction::Left;
            tile.first-=1;
        }

    } else if (dir == Direction::Left){
        if ((theMap[tile.first-1][tile.second] == "O") || (theMap[tile.first-1][tile.second] == "F")){
            tile.first-=1;
        } else if ((theMap[tile.first][tile.second+1] == "O") || (theMap[tile.first][tile.second+1] == "F")){
            dir=Direction::Down;
            tile.second+=1;
        } else if ((theMap[tile.first][tile.second-1] == "O") || (theMap[tile.first][tile.second-1] == "F")){
            dir=Direction::Up;
            tile.second-=1;
        }

    } else if (dir == Direction::Up){
        if ((theMap[tile.first][tile.second-1] == "O") || (theMap[tile.first][tile.second-1] == "F")){
            tile.second-=1;
        } else if ((theMap[tile.first+1][tile.second] == "O") || (theMap[tile.first+1][tile.second] == "F")){
            dir=Direction::Right;
            tile.first+=1;
        } else if ((theMap[tile.first-1][tile.second] == "O") || (theMap[tile.first-1][tile.second] == "F")){
            dir=Direction::Left;
            tile.first-=1;  
        }
    }
    findRoadMap(tile, dir);
}

void Map::render(RenderWindow& window){
    RectangleShape scoreRect(Vector2f(MENU_X, MENU_Y-theMap.size()*TILE_SIZE));
    scoreRect.setFillColor(SCORE_RECT_COLOR);
    scoreRect.setPosition(0, 0);

    RectangleShape sidebarRect(Vector2f(MENU_X-theMap[0].size()*TILE_SIZE, theMap.size()*TILE_SIZE));
    sidebarRect.setFillColor(SIDEBR_RECT_COLOR);
    sidebarRect.setPosition(theMap[0].size()*TILE_SIZE, MENU_Y-theMap.size()*TILE_SIZE);

    window.draw(scoreRect);
    window.draw(sidebarRect);

    Texture pathTexture;
    Texture towerTexture;

    if (!pathTexture.loadFromFile(PATH_TILE_ADDRESS) || !towerTexture.loadFromFile(TOWER_TILE_ADDRESS)) {
        return;
    }

    for (int y=0; y < theMap.size(); ++y) {
        for (int x =0; x < theMap[y].size(); ++x) {
            Sprite tileSprite;
            if (theMap[y][x] == "-") {
                tileSprite.setTexture(towerTexture);
            }
            else {
                tileSprite.setTexture(pathTexture);
            }
            tileSprite.setScale(0.2f, 0.2f);
            tileSprite.setPosition(x * TILE_SIZE, MENU_Y + (y-theMap.size()) * TILE_SIZE);
            window.draw(tileSprite); 
             
        }       
    }
}

vector<vector<string>> Map::getTheMap() const { return theMap; }
pair<int,int> Map::getStartingPoint() const { return startingPoint; }
vector<pair<int,int>> Map::getRoadMap() const { return roadMap; }