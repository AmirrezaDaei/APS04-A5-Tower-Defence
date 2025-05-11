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

class Map
{
public:
    Map(int map_width_, int map_height_, vector<string> map, shared_ptr<TextureManager> texture_manager);
    Vector2f getStartPoint() {return start_point;}
    void constructBalloons(Vector2f position, vector<AttackWave> waves);
    void drawTiles(RenderWindow& window);
    void drawBalloons(RenderWindow& window, float dt);
    void drawTowers(RenderWindow& window);
    bool isPath(Vector2f position, Vector2i v_dir);
    bool plantTower(Vector2i mouspos, shared_ptr<ShopTower> tower);
private:
    Clock balloonClock;
    shared_ptr<TextureManager> texture_manager;
    Vector2f start_point;
    Vector2f finish_point;
    vector<shared_ptr<Tile>> path_tiles;
    vector<shared_ptr<Tile>> tiles;
    vector<shared_ptr<Tower>> towers;
    vector<shared_ptr<Balloon>> balloons;
    int map_height;
    int map_width;
};

#endif // define MAP_HPP