#include "balloon.hpp"

Balloon::Balloon(Texture& texture_, Vector2f position_, Vector2i v_dir_, float speed_, int point_) : 
    texture(texture_), position(position_), v_dir(v_dir_), speed(speed_), point(point_) {
        Vector2u tex_size = texture.getSize();
        sprite.setTexture(texture);
        sprite.setPosition(position);
        sprite.setScale(BALLOON_SIZE / tex_size.x, BALLOON_SIZE / tex_size.x);
        sprite.setOrigin(tex_size.x / 2, tex_size.y / 2);
    }

void Balloon::draw(RenderWindow& window) {
    window.draw(this->sprite);
}

void Balloon::turnLeft() {
    Vector2i new_dir;
    
    new_dir.x = v_dir.y;
    new_dir.y = -v_dir.x;
    v_dir = new_dir;
}

void Balloon::turnRight() {
    Vector2i new_dir;
    new_dir.x = -v_dir.y;
    new_dir.y = v_dir.x;
    v_dir = new_dir;
}