#include "../include/tile.hpp"

Tile::Tile(char type_, Vector2f position_, Texture& texture_) : type(type_), 
position(position_), texture(texture_), has_tower(false) 
{
    sprite.setTexture(texture_);
    Vector2u tex_size = texture_.getSize();
    sprite.setScale(TILE_SIZE / tex_size.x, TILE_SIZE / tex_size.y);
    sprite.setPosition(position);
}

void Tile::draw(RenderWindow& window)
{
    window.draw(sprite);
}