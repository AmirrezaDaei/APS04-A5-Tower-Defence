#include "balloon.hpp"

Balloon::Balloon(Texture& texture_, Vector2f position_, Vector2i v_dir_, float speed_, int point_, Texture& frozen_texture_) : 
    texture(texture_), position(position_), v_dir(v_dir_), speed(speed_), point(point_), frozen_texture(frozen_texture_) {
        Vector2u tex_size = texture.getSize();
        sprite.setTexture(texture);
        sprite.setPosition(position);
        sprite.setScale(BALLOON_SIZE / tex_size.x, BALLOON_SIZE / tex_size.x);
        sprite.setOrigin(tex_size.x / 2, tex_size.y * 2 / 3);

        frozen_sprite.setTexture(frozen_texture_);
        frozen_sprite.setScale(BALLOON_SIZE / frozen_texture_.getSize().x, BALLOON_SIZE / frozen_texture_.getSize().x);
        frozen_sprite.setOrigin(frozen_texture_.getSize().x / 2, frozen_texture_.getSize().y * 2 / 3);
    }

void Balloon::draw(RenderWindow& window) {
    if (is_frozen == true)
    {
        frozen_sprite.setPosition(this->getPosition());
        window.draw(frozen_sprite);
    }
    else
    {
        window.draw(sprite);
    }
}

void Balloon::move(float dt) {
    if (clock.getElapsedTime().asSeconds() >= FREEZE_TIME)
        is_frozen = false;
    if (is_frozen == false)
    {
    sprite.move(v_dir.x * dt * speed, v_dir.y * dt * speed);
    position = sprite.getPosition();
    }
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

void Balloon::freeze() {
    is_frozen = true;
    clock.restart();
}

void Normal::pop() {
    cout << "Normal" << endl;
}

void Pregnant::pop() {
    cout << "Pregnant" << endl;
}