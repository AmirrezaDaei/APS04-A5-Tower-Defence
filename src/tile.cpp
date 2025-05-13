#include "tile.hpp"

Tile::Tile(char type_, Vector2f position_, Texture& texture_) : type(type_), 
position(position_), texture(texture_), tower(nullptr) 
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

bool Tile::contains(Vector2i mousepos)
{
    return sprite.getGlobalBounds().contains(mousepos.x, mousepos.y);
}
bool Tile::canPlantTower()
{
    if (tower == nullptr && type == GRASS)
        return true;
    else
        return false;
}

void Tile::plantTower(shared_ptr<Tower> tower_)
{
    tower = tower_;
}