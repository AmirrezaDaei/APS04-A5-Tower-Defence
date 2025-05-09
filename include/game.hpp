#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "map.hpp"
#include "scoreboard.hpp"
#include "tile.hpp"
#include "balloon.hpp"

using namespace std;

class Game
{
public:
    Game();
    void run();

private:
    void updateWindow(float dt);
    shared_ptr<Map> game_map;
    shared_ptr<ScoreBoard> score_board;
    RenderWindow window;
    PlayerStats player_stats;
    GameState state;
};

#endif // define GAME_HPP