#ifndef TOWER_HPP
#define TOWER_HPP

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iomanip>
#include "constants.hpp"
using namespace sf;

class Tower
{
public:
    Tower(Vector2f position_, int price_,float cool_down_, Texture& texture_, float radius_);
    void virtual draw(RenderWindow &window);
protected:
    Vector2f position;
    int price;
    float radius;
    float cool_down;
    Texture texture;
    Sprite sprite;
};

class ShopTower : public Tower
{
public:
    ShopTower(Vector2f position_,string name_ ,int price_, float size_, float cool_down_, Texture& texture_, float radius_);
    void draw(RenderWindow &window);
    int getPrice();
    float getRadius();
    float getCoolDownTime();
    Texture& getTexture();
    void highlight(RenderWindow& window);
    void setAvailblity(bool status);
    bool containsMouse(Vector2i mouse_pos);
    void handleBeingHovered(RenderWindow& window);
private:
    string name;
    float size;
    bool availble;
};

class FireTower : public Tower
{
    
};

#endif // define TOWER_HPP