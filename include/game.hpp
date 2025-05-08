#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "map.hpp"
#include "tile.hpp"
#include "balloon.hpp"

using namespace std;

class Game
{
public:
    Game();
    void run();

private:
    void updateWindow();
    shared_ptr<Map> game_map;
    RenderWindow window;
};

#endif // define GAME_HPP