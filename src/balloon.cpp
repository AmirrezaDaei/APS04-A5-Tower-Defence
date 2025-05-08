#include "balloon.hpp"

Balloon::Balloon(Texture& texture_, Vector2f position_, int speed_, int point_) : 
    texture(texture_), position(position_), speed(speed_), point(point_) {
        sprite.setTexture(texture);
        sprite.setPosition(position);
        sprite.setOrigin(24, 24);
    }

void Balloon::drawBalloon(RenderWindow& window) {
    window.draw(sprite);
}