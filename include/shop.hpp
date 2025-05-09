#ifndef SHOP_HPP
#define SHOP_HPP

#include <fstream>
#include <sstream>
#include <memory>
#include "tower.hpp"
#include "texturemanager.hpp"

class Shop
{
public:
    Shop(shared_ptr<TextureManager> texture_manager_, RenderWindow& window);
    void drawShop(RenderWindow& window);
    void handleTowerBeingHovered(Vector2f mouse_pos);
private:
    vector<shared_ptr<ShopTower>> towers_in_shop;
    shared_ptr<TextureManager> texture_manager;
    shared_ptr<ShopTower> hovered_tower;
};

#endif // define SHOP_HPP