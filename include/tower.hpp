#ifndef TOWER_HPP
#define TOWER_HPP

#include <SFML/Graphics.hpp>
#include "constants.hpp"
using namespace sf;

class Tower
{
public:
    Tower(Vector2f position_, int price_, float radius_,float cool_down_, Texture& texture_);
    void virtual draw(RenderWindow &window);
protected:
    Vector2f position;
    int price;
    float radius;
    float size;
    float cool_down;
    Texture texture;
    Sprite sprite;
};

class ShopTower : public Tower
{
public:
    ShopTower(Vector2f position_,string name_ ,int price_, float radius_, float size_, float cool_down_, Texture& texture_);
    void draw(RenderWindow &window);
    int getPrice();
    float getRadius();
    float getCoolDownTime();
    Texture& getTexture();
private:
    string name;
    float size;
};

#endif // define TOWER_HPP