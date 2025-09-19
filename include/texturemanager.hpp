#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

using namespace std;
using namespace sf;

class TextureManager {
public:
    Texture &getTexture(string filename);

private:
    map<string, Texture> textures;
};

#endif  // define TEXTURE_MANAGER_HPP