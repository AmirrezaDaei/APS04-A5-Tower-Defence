#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "texturemanager.hpp"
#include "tile.hpp"
#include "constants.hpp"

using namespace std;
using namespace sf;

class Map
{
public:
    Map(int map_width_, int map_height_);
    void constructTiles(vector<string> map);
    void drawTiles(RenderWindow& window);
private:
    shared_ptr<TextureManager> texture_manager;
    vector<shared_ptr<Tile>> tiles;
    int map_height;
    int map_width;
};

#endif // define MAP_HPP