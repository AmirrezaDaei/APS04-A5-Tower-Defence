#ifndef CONSTS_HPP
#define CONSTS_HPP

#include <iostream>
using namespace std;

const float TILE_SIZE = 75.f;
const float HEART_SIZE = 40.f;
const float HEALTHBAR_LENGTH = 160.F;
const float HEALTHBAR_WIDTH =  20.F;
const unsigned int SHOP_WIDTH = 250;
const unsigned int SCORE_BOARD_HEIGHT = 180;

const string BUILDABLE_TILE_FILENAME = "assets/sprites/extra_sprite/tiles/buildable_tile.png";
const string PATH_TILE_FILENAME = "assets/sprites/extra_sprite/tiles/path_tile.png";
const string NORMAL_SHOOTER_FILENAME = "assets/sprites/normal_shooter.png";
const string ICE_SHOOTER_FILENAME = "assets/sprites/ice_shooter.png";
const string CANNON_FILENAME = "assets/sprites/cannon.png";
const string HEART_FILENAME = "assets/sprites/heart.png";
const string MAP_FILENAME = "map.txt";

const string SCORE_BOARD_FONT_FILENAME = "assets/sprites/fonts/Orbitron.ttf";

const float MAX_HEALTH = 40.f;
const int INITIAL_MONEY = 200;;

struct PlayerStats
{
    int round = 1;
    float health = MAX_HEALTH;
    int money = INITIAL_MONEY;
};


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