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
    void virtual draw(RenderWindow &window) = 0;
    bool containsMouse(Vector2i mousepos);
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
    string getName();
    int getPrice();
    float getRadius();
    float getCoolDownTime();
    Texture& getTexture();
    void handleBeingHovered(RenderWindow& window);
    void highlight(RenderWindow& window);
    void setAvailblity(bool status);
private:
    string name;
    float size;
    bool availble;
};

class GameTower : public Tower
{
public:
    GameTower(Vector2f position_, int price_,float cool_down_, Texture& texture_, float radius_);
    void draw(RenderWindow& window);
protected:
    CircleShape radius_circle;
};

class FireTower : public GameTower
{
public:
    FireTower(Vector2f position_, int price_,float cool_down_, Texture& texture_, float radius_);

};

class IceTower : public GameTower
{
public:
    IceTower(Vector2f position_, int price_,float cool_down_, Texture& texture_, float radius_);
};

class Cannon : public GameTower
{
public:
    Cannon(Vector2f position_, int price_,float cool_down_, Texture& texture_, float radius_);
};

#endif // define TOWER_HPP