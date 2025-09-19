#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>
#include <list>
#include <memory>
#include <random>
#include <vector>

#include "balloon.hpp"
#include "constants.hpp"
#include "soundmanager.hpp"
#include "texturemanager.hpp"
#include "tile.hpp"
#include "tower.hpp"
#include "waves_config.hpp"

using namespace std;
using namespace sf;

class Map {
public:
    Map(int map_width_, int map_height_, vector<string> map, shared_ptr<TextureManager> texture_manager_, shared_ptr<SoundManager> sound_manager_,
        int &money_, float &health_);
    Vector2f getStartPoint() { return start_point; }
    void constructNormal(Vector2f position, Vector2i start_v_dir);
    void constructPregnant(Vector2f position, Vector2i start_v_dir);
    void drawTiles(RenderWindow &window);
    void drawBalloons(RenderWindow &window, float dt);
    void drawTowers(RenderWindow &window, float dt);
    bool isPath(Vector2f position, Vector2i v_dir);
    bool plantTower(Vector2i mouspos, shared_ptr<ShopTower> tower);
    void handleTowersAiming();
    void setStartDir(vector<string> map, int i, int j);
    Vector2i getStartVDir() { return start_dir; }
    bool isBalloonsPopped();
    void spawnNormalBalloon(Vector2f pos, Vector2i dir);

private:
    shared_ptr<TextureManager> texture_manager;
    shared_ptr<SoundManager> sound_manager;
    Vector2f start_point;
    Vector2f finish_point;
    Vector2i start_dir;
    vector<shared_ptr<Tile>> path_tiles;
    vector<shared_ptr<Tile>> tiles;
    vector<shared_ptr<GameTower>> towers;
    list<shared_ptr<Balloon>> balloons;
    int &money;
    float &health;
    int map_height;
    int map_width;
};

#endif  // define MAP_HPP