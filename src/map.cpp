#include "map.hpp"

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
                path_tiles.push_back(new_tile);
                if(map[i][j] == 'S')
                    start_point = Vector2f(j * TILE_SIZE + TILE_SIZE / 2, i * TILE_SIZE + TILE_SIZE / 2);
                if(map[i][j] == 'F')
                    finish_point = Vector2f(j * TILE_SIZE + TILE_SIZE / 2, i * TILE_SIZE + TILE_SIZE / 2);
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
    shared_ptr<Balloon> new_balloon = make_shared<Balloon>(texture, position, Vector2i(1, 0), 225, 2);
    balloons.push_back(new_balloon);
}

void Map::drawTiles(RenderWindow &window)
{
    for (auto tile : tiles)
        tile->draw(window);
}

void Map::drawTowers(RenderWindow& window)
{
    for (auto tower : towers)
    {
        tower->draw(window);
    }
}

void Map::drawBalloons(RenderWindow &window, float dt) {
    for(auto it = balloons.begin(); it != balloons.end();) {
        auto& balloon = *it;
        balloon->move(dt);
        Vector2f pos = balloon->getPosition();
        Vector2i current_dir = balloon->getVDir();
        if(!this->isPath(pos, current_dir)) {
            Vector2i right_dir = Vector2i(-current_dir.y, current_dir.x);
            Vector2i left_dir  = Vector2i(current_dir.y, -current_dir.x);
            if (this->isPath(pos, right_dir))
                balloon->turnRight();
            else if (this->isPath(pos, left_dir))
                balloon->turnLeft();
            else {
                it = balloons.erase(it);
                continue;
            }
        }
        balloon->draw(window);
        ++it;
    }
}

bool Map::isPath(Vector2f position, Vector2i v_dir) {
    Vector2f check_pos;
    check_pos.x = position.x + v_dir.x * TILE_SIZE / 2 + v_dir.x;
    check_pos.y = position.y + v_dir.y * TILE_SIZE / 2 + v_dir.y;
    for(auto& tile : path_tiles) {
        if(tile->getSprite().getGlobalBounds().contains(check_pos)) {
            return true;
        }
    }
    return false;
}

bool Map::plantTower(Vector2i mouspos, shared_ptr<ShopTower> tower)
{
    for (auto tile : tiles)
    {
        if (tile->contains(mouspos))
            if (tile->canPlantTower() == true)
            {
                Vector2f position = tile->getPosition();
                position.x = position.x;
                position.y = position.y;
                shared_ptr<Tower> new_tower = make_shared<Tower>(position, tower->getPrice(), tower->getCoolDownTime(), tower->getTexture(),
                    tower->getRadius());
                towers.push_back(new_tower);
                tile->plantTower(new_tower);
                return true;
            }
    }
    return false;
}