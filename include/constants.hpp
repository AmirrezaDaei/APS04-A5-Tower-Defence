#ifndef CONSTS_HPP
#define CONSTS_HPP

#include <iostream>
using namespace std;

const float TILE_SIZE = 100.f;
const unsigned int SHOP_WIDTH = 250;
const unsigned int WINDOW_POS_X = 300;
const unsigned int WINDOW_POS_Y = 100;

const string BUILDABLE_TILE_FILENAME = "assets/sprites/extra_sprite/tiles/buildable_tile.png";
const string PATH_TILE_FILENAME = "assets/sprites/extra_sprite/tiles/path_tile.png";
const string NORMAL_SHOOTER_FILENAME = "assets/sprites/normal_shooter.png";
const string ICE_SHOOTER_FILENAME = "assets/sprites/ice_shooter.png";
const string CANNON_FILENAME = "assets/sprites/cannon.png";
const string MAP_FILENAME = "map.txt";

enum GameState
{
    MENU,
    SETTINGS,
    PREPARING_FOR_ROUND,
    PLAYING,
    PAUSED,
    GAME_WON,
    GAME_OVER
}; 

#endif // define CONSTS_HPP