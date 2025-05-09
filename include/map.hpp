#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <memory>
#include "texturemanager.hpp"
#include "tile.hpp"
#include "constants.hpp"
#include "balloon.hpp"

using namespace std;
using namespace sf;

class Map
{
public:
    Map(int map_width_, int map_height_, vector<string> map, shared_ptr<TextureManager> texture_manager);
    void constructBalloons(Vector2f position);
    void drawTiles(RenderWindow& window);
    void drawBalloons(RenderWindow& window);
private:
    shared_ptr<TextureManager> texture_manager;
    vector<shared_ptr<Tile>> tiles;
    vector<shared_ptr<Balloon>> balloons;
    int map_height;
    int map_width;
};

#endif // define MAP_HPP