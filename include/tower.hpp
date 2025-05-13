#ifndef TOWER_HPP
#define TOWER_HPP

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iomanip>
#include <memory>
#include <cmath>
#include "balloon.hpp"
#include "constants.hpp"
using namespace sf;

class Tower
{
public:
    Tower(Vector2f position_, int price_,float cooldown_, Texture& texture_, float radius_);
    void virtual draw(RenderWindow &window) = 0;
    bool containsMouse(Vector2i mousepos);
    float getRadius() { return radius; }
    float getCoolDownTime() { return cooldown; }
protected:
    Vector2f position;
    int price;
    float radius;
    float cooldown;
    Texture texture;
    Sprite sprite;
};

class ShopTower : public Tower
{
public:
    ShopTower(Vector2f position_,string name_ ,int price_, float size_, float cooldown_, Texture& texture_, float radius_);
    void draw(RenderWindow &window);
    string getName() { return name; }
    int getPrice() { return price; }
    Texture& getTexture() { return texture; }
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
    bool isReady();
    bool isInRange(Vector2f pos);
    void virtual selectEnemy(vector<shared_ptr<Balloon>> enemiesInRange) = 0;
    void rotateTower();
protected:
    CircleShape radius_circle;
    Clock clock;
    shared_ptr<Balloon> lockedInEnemy  = nullptr;
};

float getDistance(Vector2f pos1, Vector2f pos2);

class FireTower : public GameTower
{
public:
    FireTower(Vector2f position_, int price_,float cool_down_, Texture& texture_, float radius_);
    void selectEnemy(vector<shared_ptr<Balloon>> enemiesInRange);

};

class IceTower : public GameTower
{
public:
    IceTower(Vector2f position_, int price_,float cool_down_, Texture& texture_, float radius_);
    void selectEnemy(vector<shared_ptr<Balloon>> enemiesInRange);
};

class Cannon : public GameTower
{
public:
    Cannon(Vector2f position_, int price_,float cool_down_, Texture& texture_, float radius_);
    void selectEnemy(vector<shared_ptr<Balloon>> enemiesInRange);
};

#endif // define TOWER_HPP