#include "../include/map.hpp"

Map::Map(int map_width_, int map_height_, vector<string> map, shared_ptr<TextureManager> texture_manager_) : 
map_width(map_width_), map_height(map_height_), texture_manager(texture_manager_)
{
    for (int i = 0; i < map_height; i++)
    {
        for (int j = 0; j < map_width; j++)
        {
            Vector2f position(j * TILE_SIZE, i * TILE_SIZE);
            shared_ptr<Tile> new_tile;

            if (map[i][j] == 'O' || map[i][j] == 'S' || map[i][j] == 'F')
            {
                Texture &texture = texture_manager->getTexture(PATH_TILE_FILENAME);
                new_tile = make_shared<Tile>(map[i][j], position, texture);
            }

            else if (map[i][j] == '-')
            {
                Texture &texture = texture_manager->getTexture(BUILDABLE_TILE_FILENAME);
                new_tile = make_shared<Tile>(map[i][j], position, texture);
            }

            tiles.push_back(new_tile);
        }
    }
}

void Map::constructBalloons(Vector2f position) {
    Texture &texture = texture_manager->getTexture(BALLOON_FILENAME);
    shared_ptr<Balloon> new_balloon = make_shared<Balloon>(texture, position, 2, 2);
    balloons.push_back(new_balloon);
}

void Map::drawTiles(RenderWindow &window)
{
    for (auto tile : tiles)
        tile->draw(window);
}

void Map::drawBalloons(RenderWindow &window) {
    for(auto balloon : balloons)
        balloon->draw(window);
}