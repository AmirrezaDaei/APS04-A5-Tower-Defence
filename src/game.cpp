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

    gameMap = make_shared<Map>(map_width, map_height);
    gameMap->constructTiles(map);

    input.close();
}

void Game::updateWindow()
{
    gameMap->drawTiles(window);
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