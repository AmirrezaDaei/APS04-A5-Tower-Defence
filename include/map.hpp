#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <memory>
#include <cmath>
#include "texturemanager.hpp"
#include "tile.hpp"
#include "constants.hpp"
#include "balloon.hpp"

using namespace std;
using namespace sf;

class Map
{
public:
    Map(int map_width_, int map_height_, vector<string> map);
    Vector2f getStartPoint() {return start_point;}
    void constructBalloons(Vector2f position);
    void drawTiles(RenderWindow& window);
    void drawBalloons(RenderWindow& window, float dt);
    bool isPath(Vector2f position, Vector2i v_dir);
    bool isCenteredOnTile(Vector2f pos) {
        // cout << int(TILE_SIZE / 2) << endl;
        // cout << (int(pos.x) % int(TILE_SIZE)) - int(TILE_SIZE / 2) << " " << (int(pos.y) % int(TILE_SIZE)) - int(TILE_SIZE/ 2) << endl;
        // return ((int(pos.x) % int(TILE_SIZE)) - int(TILE_SIZE / 2) < 10 && (int(pos.y) % int(TILE_SIZE)) - int(TILE_SIZE/ 2) < 10);
    }
private:
    shared_ptr<TextureManager> texture_manager;
    Vector2f start_point;
    Vector2f finish_point;
    vector<shared_ptr<Tile>> path_tiles;
    vector<shared_ptr<Tile>> tiles;
    vector<shared_ptr<Balloon>> balloons;
    int map_height;
    int map_width;
};

#endif // define MAP_HPP