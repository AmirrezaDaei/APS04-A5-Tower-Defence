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
    Shop(shared_ptr<TextureManager> texture_manager_, RenderWindow& window, int& money_);
    void drawShop(RenderWindow& window);
    void handleTowerBeingHovered(Vector2i mouse_pos);
    shared_ptr<ShopTower>  handleBuyingTower(Vector2i mouse_pos);
    void abortBuying();
private:
    vector<shared_ptr<ShopTower>> towers_in_shop;
    int& money;
    shared_ptr<TextureManager> texture_manager;
    shared_ptr<ShopTower> hovered_tower;
    shared_ptr<ShopTower> tower_to_buy = nullptr;
};

#endif // define SHOP_HPP