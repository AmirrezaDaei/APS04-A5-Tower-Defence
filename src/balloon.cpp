#include "../include/balloon.hpp"

Balloon::Balloon(Texture& texture_, Vector2f position_, float speed_, int point_) : 
    texture(texture_), position(position_), speed(speed_), point(point_) {
        Vector2u tex_size = texture.getSize();
        sprite.setTexture(texture);
        sprite.setPosition(position);
        sprite.setScale(BALLOON_SIZE / tex_size.x, BALLOON_SIZE / tex_size.x);
        sprite.setOrigin(tex_size.x / 2, tex_size.y / 2);
    }

void Balloon::draw(RenderWindow& window) {
    window.draw(this->sprite);
}

void Balloon::moveUp(float dt) {
    this->sprite.move(0, -dt * speed);
}

void Balloon::moveDown(float dt) {
    this->sprite.move(0, dt * speed);
}

void Balloon::moveRight(float dt) {
    this->sprite.move(dt * speed, 0);
}

void Balloon::moveLeft(float dt) {
    this->sprite.move(-dt * speed, 0);
}