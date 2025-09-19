#ifndef BALLOON_HPP
#define BALLOON_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

#include "constants.hpp"
#include "soundmanager.hpp"
using namespace sf;

class Balloon {
public:
    Balloon(Texture &texture_, Vector2f position_, Vector2i v_dir, float speed, int point_, Texture &frozen_texture_,
        shared_ptr<SoundManager> sound_manager_);
    Vector2f getPosition() { return position; }
    Vector2i getVDir() { return v_dir; }
    float getSpeed() { return speed; }
    int getPoint() { return point; }
    virtual void draw(RenderWindow &window);
    BalloonType getType() { return type; }
    void move(float dt);
    void turnLeft();
    void turnRight();
    bool isLockedOn() { return locked_on; }
    void setLockedOn() { locked_on = true; }
    BalloonState getState() { return state; }
    void freeze();
    void pop();

protected:
    Vector2i v_dir;
    Vector2f position;
    float speed;
    int point;
    Texture texture;
    Texture frozen_texture;
    Sprite sprite;
    Sprite frozen_sprite;
    shared_ptr<SoundManager> sound_manager;
    BalloonState state = NORMAL_STATE;
    bool locked_on = false;
    Clock clock;
    BalloonType type;
};

class Normal : public Balloon {
public:
    Normal(Texture &texture_, Vector2f position_, Vector2i v_dir, float speed, int point_, Texture &frozen_texture_, Texture &popped_texture_,
        shared_ptr<SoundManager> sound_manager_);
    void draw(RenderWindow &window);

private:
    Texture popped_texture;
    Sprite popped_sprite;
};

class Pregnant : public Balloon {
public:
    Pregnant(Texture &texture_, Vector2f position_, Vector2i v_dir, float speed, int point_, Texture &frozen_texture_,
        shared_ptr<SoundManager> sound_manager_);
};

#endif  // define BALLOON_HPP