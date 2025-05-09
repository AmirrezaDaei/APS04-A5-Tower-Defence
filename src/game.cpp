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

    window.create(VideoMode((unsigned int)(TILE_SIZE * map_width + SHOP_WIDTH), (unsigned int)(TILE_SIZE * map_height)), "Tower Defence",
    Style::Titlebar | Style::Close);
    window.setPosition(sf::Vector2i(WINDOW_POS_X, WINDOW_POS_Y));


    game_map = make_shared<Map>(map_width, map_height, map);

    score_board = make_shared<ScoreBoard>(window);



    input.close();
}

void Game::updateWindow()
{
    game_map->drawTiles(window);
    score_board->draw(window);
    //game_map->drawShop;
}

void Game::run()
{
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color(200, 200, 200));
        updateWindow();
        window.display();
    }
}