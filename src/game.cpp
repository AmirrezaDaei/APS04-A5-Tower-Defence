#include "game.hpp"

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
    window.setPosition(Vector2i((desktop.width - window.getSize().x) / 2, (desktop.height - window.getSize().y) / 2));

    shared_ptr<TextureManager> texture_manager = make_shared<TextureManager>();
    game_map = make_shared<Map>(map_width, map_height, map, texture_manager);
    game_map->constructBalloons(game_map->getStartPoint(), ATTACKING_PLAN);
    game_shop = make_shared<Shop>(texture_manager, window, player_stats.money);
    score_board = make_shared<ScoreBoard>(window);
    input.close();        
}

void Game::updateWindow(float dt)
{
    game_map->drawTiles(window);
    game_map->drawBalloons(window, dt);
    game_map->drawTowers(window, dt);
    score_board->drawScoreBoard(window, player_stats);
    game_shop->drawShop(window);
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
            {
                window.close();
            }    
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    Vector2i mousePos = Mouse::getPosition(window);
                    chosen_tower = game_shop->handleBuyingTower(mousePos);
                    if (chosen_tower != NULL)
                    {
                        bool bought = game_map->plantTower(mousePos, chosen_tower);
                        if (bought == true)
                        {
                            player_stats.money -= chosen_tower->getPrice();
                            game_shop->abortBuying();
                        }
                        chosen_tower = nullptr;
                    }
                }
                if (event.mouseButton.button == Mouse::Right)
                {
                    chosen_tower = nullptr;
                    game_shop->abortBuying();
                }
            }
        }
        float dt = clock.restart().asSeconds();


        Vector2i mouse_pos = Mouse::getPosition(window);
        game_shop->handleTowerBeingHovered(mouse_pos);

        game_map->handleTowersAiming();
        window.clear();
        updateWindow(dt);
        window.display();
    }
}