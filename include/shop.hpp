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
private:
    vector<shared_ptr<ShopTower>> towers_in_shop;
    shared_ptr<TextureManager> texture_manager;
};

#endif // define SHOP_HPP