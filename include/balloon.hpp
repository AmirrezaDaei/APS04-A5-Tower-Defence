#ifndef BALLOON_HPP
#define BALLOON_HPP

#include <SFML/Graphics.hpp>
#include "constants.hpp"
using namespace sf;

class Balloon
{
public:
    Balloon(Texture &texture_, Vector2f position_, Vector2i v_dir, float speed, int point_);
    Vector2f getPosition();
    Vector2i getVDir() { return v_dir; }
    float getSpeed() { return speed; }
    void draw(RenderWindow &window);
    void move(float dt);
    void turnLeft();
    void turnRight();
    bool isLockedOn() { return locked_on; }
    void setLockedOn() { locked_on = true; }
    bool isFrozen() { return is_frozen; }
    void freeze() { is_frozen = true; clock.restart();}
private:
    Vector2i v_dir;
    float speed;
    int point;
    Vector2f position;
    Texture texture;
    Sprite sprite;
    bool is_destroyed = false;
    bool is_frozen = false;
    bool locked_on = false;
    Clock clock;
};

#endif // define BALLOON_HPP