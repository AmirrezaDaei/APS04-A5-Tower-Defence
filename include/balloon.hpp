#ifndef BALLOON_HPP
#define BALLOON_HPP

#include <SFML/Graphics.hpp>
#include "constants.hpp"

using namespace sf;

class Balloon {
    public:
        Balloon(Texture& texture_, Vector2f position_, float speed_, int point_);
        void draw(RenderWindow& window);
        void moveUp(float dt);
        void moveDown(float dt);
        void moveRight(float dt);
        void moveLeft(float dt);
    private:
        float speed;
        int point;
        Vector2f position;
        Texture texture;
        Sprite sprite;
        bool is_destroyed = false;
};


#endif // define BALLOON_HPP