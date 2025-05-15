#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <memory>
#include <cmath>
#include <random>
#include "texturemanager.hpp"
#include "tower.hpp"
#include "tile.hpp"
#include "constants.hpp"
#include "balloon.hpp"
#include "wave_configs.hpp"

using namespace std;
using namespace sf;

class Map {
public:
    Map(int map_width_, int map_height_, vector<string> map, shared_ptr<TextureManager> texture_manager);
    Vector2f getStartPoint() {return start_point;}
    void constructBalloons(Vector2f position);
    void drawTiles(RenderWindow& window);
    void drawBalloons(RenderWindow& window, float dt);
    void drawTowers(RenderWindow& window, float dt);
    bool isPath(Vector2f position, Vector2i v_dir);
    bool plantTower(Vector2i mouspos, shared_ptr<ShopTower> tower);
    void handleTowersAiming();
    void setStartDir(vector<string> map, int i, int j);
    bool isBalloonsPopped();
private:
    shared_ptr<TextureManager> texture_manager;
    Vector2f start_point;
    Vector2f finish_point;
    Vector2i start_dir;
    vector<shared_ptr<Tile>> path_tiles;
    vector<shared_ptr<Tile>> tiles;
    vector<shared_ptr<GameTower>> towers;
    vector<shared_ptr<Balloon>> balloons;
    int map_height;
    int map_width;
};

#endif // define MAP_HPP