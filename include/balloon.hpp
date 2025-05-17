#ifndef BALLOON_HPP
#define BALLOON_HPP

#include <SFML/Graphics.hpp>
#include "constants.hpp"
using namespace sf;

class Balloon {
public:
    Balloon(Texture& texture_, Vector2f position_, Vector2i v_dir, float speed, int point_, Texture& frozen_texture_);
    Vector2f getPosition() { return position; }
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
    // virtual void pop() = 0;
protected:
    Vector2i v_dir;
    Vector2f position;
    float speed;
    int point;
    Texture texture;
    Texture frozen_texture;
    Sprite sprite;
    Sprite frozen_sprite;
    bool is_destroyed = false;
    bool is_frozen = false;
    bool locked_on = false;
    Clock clock;
};

class Normal : public Balloon {
public:
    Normal(Texture& texture_, Vector2f position_, Vector2i v_dir, float speed, int point_, Texture& frozen_texture_)
    : Balloon(texture_, position_, v_dir, speed, point_,frozen_texture_) {}
    void pop();
};

class Pregnant : public Balloon{
public:
    Pregnant(Texture& texture_, Vector2f position_, Vector2i v_dir, float speed, int point_, Texture& frozen_texture_)
    : Balloon(texture_, position_, v_dir, speed, point_, frozen_texture_) {}
    void pop();
    // void replicate();
};

#endif // define BALLOON_HPP