#include "../include/tower.hpp"

Tower::Tower(Vector2f position_, int price_, float radius_,float cool_down_, Texture& texture_)
: position(position_), price(price_), radius(radius_) ,cool_down(cool_down_), texture(texture_)
{
    sprite.setTexture(texture_);
    Vector2u tex_size = texture_.getSize();
    sprite.setScale(TOWER_SIZE / tex_size.x, TOWER_SIZE / tex_size.y);
    sprite.setPosition(position);
}

void Tower::draw(RenderWindow& window)
{
    window.draw(sprite);
}

ShopTower::ShopTower(Vector2f position_, string name_,int price_, float radius_, float size_, float cool_down_, Texture& texture_)
: Tower(position_,price_, size_, cool_down_, texture_), name(name_), size(size_) {}

void ShopTower::draw(RenderWindow &window)
{
    Vector2u tex_size = texture.getSize();
    sprite.setScale(size / tex_size.x, size / tex_size.y);
    window.draw(sprite);
}

int ShopTower::getPrice() { return price; }

float ShopTower::getRadius() { return radius; }

float ShopTower::getCoolDownTime() { return cool_down; }

Texture& ShopTower::getTexture() {return texture; }