#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include "constants.hpp"
using namespace sf;

class Tile
{
public:
    Tile(char type_, Vector2f position_, Texture& texture_);
    void draw(RenderWindow& window);
private:
    char type;
    bool has_tower;
    Vector2f position;
    Texture texture;
    Sprite sprite;
};


#endif // define TILE_HPP