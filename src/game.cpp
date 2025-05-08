#include "../include/game.hpp"

Game::Game()
{
    ifstream input(MAP_FILENAME);
    string line;
    vector<string> map;

    while (getline(input, line))
        map.push_back(line);

    int map_height = map.size();
    int map_width = map[0].size();

    window.create(VideoMode((unsigned int)(TILE_SIZE * map_width + SHOP_WIDTH), (unsigned int)(TILE_SIZE * map_height)), "Tower Defence");

    game_map = make_shared<Map>(map_width, map_height);
    game_map->constructTiles(map);
    Vector2f position(200.f, 200.f); // temporary. We should add a start point getter to map then get a random position within estimated coordinates
    game_map->constructBalloons(position);
    input.close();
}

void Game::updateWindow()
{
    window.clear();
    game_map->drawTiles(window);
    game_map->drawBalloons(window);
}

void Game::run()
{
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        updateWindow();
        window.display();
    }
}