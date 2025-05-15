#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "map.hpp"
#include "shop.hpp"
#include "scoreboard.hpp"
#include "tile.hpp"
#include "balloon.hpp"
#include "wave_configs.hpp"

using namespace std;

class Game
{
public:
    Game();
    void run();

private:
    void updateWindow(float dt);
    void handleWave(float dt);
    void spawnBalloon();
    void startNewWave();
    void endWave();
    Clock clock;
    float waves_gap = 0.f;
    float balloons_gap = 0.f;
    int wave = 0;
    int balloons_spawned = 0;
    bool is_wave_active = false;
    shared_ptr<Map> game_map;
    shared_ptr<Shop> game_shop;
    shared_ptr<ScoreBoard> score_board;
    RenderWindow window;
    PlayerStats player_stats;
    GameState state;
    shared_ptr<ShopTower> chosen_tower = nullptr;
};

#endif // define GAME_HPP