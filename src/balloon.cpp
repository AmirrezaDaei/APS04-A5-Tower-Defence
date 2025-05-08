#include "../include/balloon.hpp"

Balloon::Balloon(Texture& texture_, Vector2f position_, int speed_, int point_) : 
    texture(texture_), position(position_), speed(speed_), point(point_) {
        Vector2u tex_size = texture.getSize();
        sprite.setTexture(texture);
        sprite.setPosition(position);
        sprite.setOrigin(24, 24);
    }

void Balloon::draw(RenderWindow& window) {
    window.draw(sprite);
}