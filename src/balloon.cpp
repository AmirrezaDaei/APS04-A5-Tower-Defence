#include "balloon.hpp"

Balloon::Balloon(Texture &texture_, Vector2f position_, Vector2i v_dir_, float speed_, int point_,
    Texture &frozen_texture_, shared_ptr<SoundManager> sound_manager_)
    : texture(texture_),
      position(position_),
      v_dir(v_dir_),
      speed(speed_),
      point(point_),
      frozen_texture(frozen_texture_),
      sound_manager(sound_manager_) {
    Vector2u tex_size = texture.getSize();
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale(BALLOON_SIZE / tex_size.x, BALLOON_SIZE / tex_size.x);
    sprite.setOrigin(tex_size.x / 2, tex_size.y * 2 / 3);

    frozen_sprite.setTexture(frozen_texture_);
    frozen_sprite.setScale(
        BALLOON_SIZE / frozen_texture_.getSize().x, BALLOON_SIZE / frozen_texture_.getSize().x);
    frozen_sprite.setOrigin(frozen_texture_.getSize().x / 2, frozen_texture_.getSize().y * 2 / 3);

    sound_manager->loadSound(BALLOON_FREEZE_SOUND_FILENAME);
    sound_manager->loadSound(BALLOON_POP_SOUND_FILENAME);
}

Normal::Normal(Texture &texture_, Vector2f position_, Vector2i v_dir, float speed, int point_,
    Texture &frozen_texture_, Texture &popped_texture_, shared_ptr<SoundManager> sound_manager_)
    : Balloon(texture_, position_, v_dir, speed, point_, frozen_texture_, sound_manager_),
      popped_texture(popped_texture_) {
    type = NORMAL;
    popped_sprite.setTexture(popped_texture_);
    popped_sprite.setScale(1.5 * BALLOON_SIZE / popped_texture_.getSize().x,
        1.5 * BALLOON_SIZE / popped_texture_.getSize().x);
    popped_sprite.setOrigin(popped_texture_.getSize().x / 2, popped_texture_.getSize().y / 2);
}

Pregnant::Pregnant(Texture &texture_, Vector2f position_, Vector2i v_dir, float speed, int point_,
    Texture &frozen_texture_, shared_ptr<SoundManager> sound_manager_)
    : Balloon(texture_, position_, v_dir, speed, point_, frozen_texture_, sound_manager_) {
    type = PREGNANT;
}

void Balloon::draw(RenderWindow &window) {
    if (state == FROZEN) {
        frozen_sprite.setPosition(this->getPosition());
        window.draw(frozen_sprite);
    } else {
        window.draw(sprite);
    }
}

void Normal::draw(RenderWindow &window) {
    if (state == POPPED) {
        popped_sprite.setPosition(this->getPosition());
        window.draw(popped_sprite);
    } else {
        Balloon::draw(window);
    }
}

void Balloon::move(float dt) {
    if (clock.getElapsedTime().asSeconds() >= FREEZE_TIME && state == FROZEN) state = NORMAL_STATE;
    if (clock.getElapsedTime().asSeconds() >= POP_TIME && state == POPPED) state = DESTROYED;
    if (state == NORMAL_STATE) {
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
    state = FROZEN;
    clock.restart();
    sound_manager->playSound(BALLOON_FREEZE_SOUND_FILENAME);
}

void Balloon::pop() {
    if (type == NORMAL) {
        state = POPPED;
        clock.restart();
    } else if (type == PREGNANT) {
        state = DESTROYED;
    }
    sound_manager->playSound(BALLOON_POP_SOUND_FILENAME, 50.f);
}