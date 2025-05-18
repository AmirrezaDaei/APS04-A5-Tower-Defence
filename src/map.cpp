#include "map.hpp"

Map::Map(int map_width_, int map_height_, vector<string> map, shared_ptr<TextureManager> texture_manager_, int &money_, float &health_) : map_width(map_width_), map_height(map_height_), texture_manager(texture_manager_), money(money_), health(health_)
{
    for (int i = 0; i < map_height; i++)
    {
        for (int j = 0; j < map_width; j++)
        {
            Vector2f position(j * TILE_SIZE, i * TILE_SIZE);
            shared_ptr<Tile> new_tile;
            if (map[i][j] == PATH || map[i][j] == START || map[i][j] == FINISH)
            {
                Texture &texture = texture_manager->getTexture(PATH_TILE_FILENAME);
                new_tile = make_shared<Tile>(map[i][j], position, texture);
                path_tiles.push_back(new_tile);
                if (map[i][j] == START)
                {
                    start_point = Vector2f(j * TILE_SIZE + TILE_SIZE / 2, i * TILE_SIZE + TILE_SIZE / 2);
                    this->setStartDir(map, i, j);
                }
                if (map[i][j] == FINISH)
                    finish_point = Vector2f(j * TILE_SIZE + TILE_SIZE / 2, i * TILE_SIZE + TILE_SIZE / 2);
            }
            else if (map[i][j] == GRASS)
            {
                Texture &texture = texture_manager->getTexture(BUILDABLE_TILE_FILENAME);
                new_tile = make_shared<Tile>(map[i][j], position, texture);
            }
            tiles.push_back(new_tile);
        }
    }
}

void Map::constructNormal(Vector2f position, Vector2i start_v_dir)
{
    Texture &texture = texture_manager->getTexture(RED_NORMAL_BALLOON_FILENAME);
    Texture &frozen_texture = texture_manager->getTexture(FROZEN_NORMAL_BALLOON_FILENAME);
    shared_ptr<Balloon> new_balloon = make_shared<Normal>(texture, position, start_v_dir, TILE_SIZE * 2, POINT, frozen_texture);
    balloons.push_back(new_balloon);
}

void Map::constructPregnant(Vector2f position, Vector2i start_v_dir)
{
    Texture &texture = texture_manager->getTexture(PREGNANT_BALLOON_FILENAME);
    Texture &frozen_texture = texture_manager->getTexture(FROZEN_PREGNANT_BALLOON_FILENAME);
    shared_ptr<Balloon> new_balloon = make_shared<Pregnant>(texture, position, start_v_dir, TILE_SIZE * 2, POINT, frozen_texture);
    balloons.push_back(new_balloon);
}

void Map::drawTiles(RenderWindow &window)
{
    for (auto tile : tiles)
        tile->draw(window);
}

void Map::drawTowers(RenderWindow &window, float dt)
{
    for (auto tower : towers)
    {
        tower->rotateTower(dt);
        tower->draw(window);
    }
}

void Map::setStartDir(vector<string> map, int i, int j)
{
    if (i + 1 < map.size())
        if (map[i + 1][j] == GRASS)
            start_dir = Vector2i(1, 0);

    if (j + 1 < map[0].size())
        if (map[i][j + 1] == GRASS)
            start_dir = Vector2i(0, -1);

    if (i - 1 >= 0)
        if (map[i - 1][j] == GRASS)
            start_dir = Vector2i(-1, 0);

    if (j - 1 >= 0)
        if (map[i][j - 1] == GRASS)
            start_dir = Vector2i(0, 1);
}

void Map::drawBalloons(RenderWindow &window, float dt) {
    for (auto it = balloons.begin(); it != balloons.end();) {
        auto& balloon = *it;
        if (balloon->isDestroyed()) {
            money += balloon->getPoint();
            if (balloon->getType() == PREGNANT) {
                if(balloon->getVDir().x == 0) {
                    spawnNormalBalloon(Vector2f(balloon->getPosition().x, balloon->getPosition().y + generateRandom(-5, 5)), balloon->getVDir());
                    spawnNormalBalloon(Vector2f(balloon->getPosition().x, balloon->getPosition().y + generateRandom(-5, 5)), balloon->getVDir());
                }
                else if(balloon->getVDir().y == 0) {
                    spawnNormalBalloon(Vector2f(balloon->getPosition().x + generateRandom(-5, 5), balloon->getPosition().y), balloon->getVDir());
                    spawnNormalBalloon(Vector2f(balloon->getPosition().x + generateRandom(-5, 5), balloon->getPosition().y), balloon->getVDir());    
                }
            }
            it = balloons.erase(it);
            continue;
        }
        balloon->move(dt);
        Vector2f pos = balloon->getPosition();
        Vector2i current_dir = balloon->getVDir();
        if (!this->isPath(pos, current_dir)) {
            Vector2i right_dir = Vector2i(-current_dir.y, current_dir.x);
            Vector2i left_dir  = Vector2i(current_dir.y, -current_dir.x);
            if (this->isPath(pos, right_dir))
                balloon->turnRight();
            else if (this->isPath(pos, left_dir))
                balloon->turnLeft();
            else {
                health -= DAMAGE;
                it = balloons.erase(it);
                continue;
            }
        }
            balloon->draw(window);
            ++it;
    }
}

void Map::spawnNormalBalloon(Vector2f pos, Vector2i dir) {
    Texture &texture = texture_manager->getTexture(PURPLE_NORMAL_BALLOON_FILENAME);
    Texture &frozen_texture = texture_manager->getTexture(FROZEN_NORMAL_BALLOON_FILENAME);
    shared_ptr<Balloon> normalBalloon = make_shared<Normal>(texture, pos, dir, TILE_SIZE, POINT, frozen_texture);
    balloons.push_back(normalBalloon);
}

bool Map::isPath(Vector2f position, Vector2i v_dir) {
    Vector2f check_pos;
    check_pos.x = position.x + v_dir.x * TILE_SIZE / 2 + v_dir.x;
    check_pos.y = position.y + v_dir.y * TILE_SIZE / 2 + v_dir.y;
    for (auto &tile : path_tiles)
        if (tile->getSprite().getGlobalBounds().contains(check_pos))
            return true;
    return false;
}

bool Map::plantTower(Vector2i mouspos, shared_ptr<ShopTower> tower)
{
    for (auto tile : tiles)
    {
        if (tile->contains(mouspos))
        {
            if (tile->canPlantTower() == true)
            {
                Vector2f position = tile->getPosition();
                position.x = position.x + TILE_SIZE / 2;
                position.y = position.y + TILE_SIZE / 2;

                shared_ptr<GameTower> new_tower;
                if (tower->getName() == NORMAL_SHOOTER)
                {
                    Texture &ray_texture = texture_manager->getTexture(FIRE_RAY_FILENAME);
                    new_tower = make_shared<FireTower>(position, tower->getPrice(), tower->getCoolDownTime(), tower->getTexture(),
                    tower->getRadius(), ray_texture);
                }

                if (tower->getName() == ICE_SHOOTER)
                {
                    Texture &ray_texture = texture_manager->getTexture(ICE_RAY_FILENAME);
                    new_tower = make_shared<IceTower>(position, tower->getPrice(), tower->getCoolDownTime(), tower->getTexture(),
                    tower->getRadius(), ray_texture);
                }

                if (tower->getName() == CANNON)
                {
                    Texture &ray_texture = texture_manager->getTexture(CANNON_RAY_FILENAME);
                    new_tower = make_shared<Cannon>(position, tower->getPrice(), tower->getCoolDownTime(), tower->getTexture(),
                    tower->getRadius(), ray_texture);
                }

                towers.push_back(new_tower);
                tile->plantTower(new_tower);
                return true;
            }
        }
    }

    return false;
}

void Map::handleTowersAiming()
{
    for (auto tower : towers)
    {
        if (tower->readyToShoot())
        {
            vector<shared_ptr<Balloon>> enemies;
            for (auto balloon : balloons)
                enemies.push_back(balloon);
            if (enemies.size() != 0)
                tower->selectEnemy(enemies);
        }
    }
    for (auto tower : towers)
    {
        tower->shootEnemy();
    }
}

bool Map::isBalloonsPopped()
{
    if (balloons.empty())
        return true;
    return false;
}