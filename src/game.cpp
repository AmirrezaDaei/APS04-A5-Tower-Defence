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
    VideoMode desktop = VideoMode::getDesktopMode();
    window.setPosition(Vector2i((desktop.width - window.getSize().x) /  2 , (desktop.height - window.getSize().y) / 2));

    shared_ptr<TextureManager> texture_manager = make_shared<TextureManager>();

    game_map = make_shared<Map>(map_width, map_height, map, texture_manager);
    game_shop = make_shared<Shop>(texture_manager, window);
    score_board = make_shared<ScoreBoard>(window);
    game_map->constructBalloons(game_map->getStartPoint());
    input.close();
}

void Game::updateWindow(float dt)
{
    game_map->drawTiles(window);
    score_board->draw(window, player_stats);
    game_shop->drawShop(window); 
    game_map->drawBalloons(window, dt);
}

void Game::run()
{
    Clock clock;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            
        }
        float dt = clock.restart().asSeconds();
        Vector2i mousePixelPos = Mouse::getPosition(window);
        Vector2f mouse_pos = window.mapPixelToCoords(mousePixelPos);
        game_shop->handleTowerBeingHovered(mouse_pos);
        window.clear(Color(200, 200, 200));
        updateWindow(dt);
        window.display();
    }
}