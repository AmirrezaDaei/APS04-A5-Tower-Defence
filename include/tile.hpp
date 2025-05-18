#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "constants.hpp"
#include "tower.hpp"

using namespace sf;

class Tile
{
public:
    Tile(char type_, Vector2f position_, Texture &texture_);
    Sprite getSprite() { return sprite; }
    Vector2f getPosition() { return position; }
    void draw(RenderWindow &window);
    bool contains(Vector2i mousepos);
    bool canPlantTower();
    void plantTower(shared_ptr<Tower> tower_);

private:
    char type;
    shared_ptr<Tower> tower;
    Vector2f position;
    Texture texture;
    Sprite sprite;
};

#endif // define TILE_HPP