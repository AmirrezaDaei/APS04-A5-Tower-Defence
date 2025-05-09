#ifndef TOWER_HPP
#define TOWER_HPP

#include <SFML/Graphics.hpp>
#include "constants.hpp"
using namespace sf;

class Tower
{
public:
Tower(Vector2f position_, int price_, float radius_, Time cool_down_, Texture texture_);
void draw(RenderWindow& window);
private:
    Vector2f position;
    int price;
    float radius;
    Time cool_down;
    Texture texture;
    Sprite sprite;
};

#endif // define TOWER_HPP