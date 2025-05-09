#include "../include/tower.hpp"

Tower::Tower(Vector2f position_, int price_, float radius_, Time cool_down_, Texture texture_)
: position(position_), price(price_), radius(radius_), cool_down(cool_down_), texture(texture_)
{
    sprite.setTexture(texture_);
    Vector2u tex_size = texture_.getSize();
    sprite.setScale(TILE_SIZE / tex_size.x, TILE_SIZE / tex_size.y);
    sprite.setPosition(position);
}

void Tower::draw(RenderWindow& window)
{
    window.draw(sprite);
}
