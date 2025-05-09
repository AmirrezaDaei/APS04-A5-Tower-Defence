#ifndef SHOP_HPP
#define SHOP_HPP

#include <memory>
#include "tower.hpp"
#include "texturemanager.hpp"

class Shop
{
public:
    Shop();
private:
    vector<Tower> tower_types;
    shared_ptr<TextureManager> texture_manager;
};

#endif // define SHOP_HPP