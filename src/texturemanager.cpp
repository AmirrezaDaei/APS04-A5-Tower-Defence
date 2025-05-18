#include "texturemanager.hpp"

Texture &TextureManager::getTexture(string filename)
{
    if (textures.find(filename) == textures.end())
    {
        Texture texture;
        if (!texture.loadFromFile(filename))
        {
            cerr << "Unable to load texture\n";
        }
        textures[filename] = texture;
    }
    return textures[filename];
}