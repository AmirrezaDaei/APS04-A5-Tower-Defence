#ifndef CONSTS_HPP
#define CONSTS_HPP

#include <iostream>
#include <random>
using namespace std;

const float TILE_SIZE = 75.f;
const float TOWER_SIZE = 65.f;
const float HEART_SIZE = 40.f;
const float HEALTHBAR_LENGTH = 160.f;
const float HEALTHBAR_WIDTH =  20.f;
const float DESCRIPTION_HEIGHT = 150.f;
const float BALLOON_SIZE = 50.f;
const float PREGNANT_SIZE = 50.f;
const unsigned int SHOP_WIDTH = 250;
const unsigned int SCORE_BOARD_HEIGHT = 180;

const char GRASS = '-';
const char PATH = 'O';
const char START = 'S';
const char FINISH = 'F';
const char COMMA_SEPERATOR = ',';

const string IMAGE_FORMAT = ".png";

const string BUILDABLE_TILE_FILENAME = "assets/sprites/extra_sprite/tiles/buildable_tile.png";
const string PATH_TILE_FILENAME = "assets/sprites/extra_sprite/tiles/path_tile.png";
const string SHOOTERS_FILEPATH = "assets/sprites/";
const string HEART_FILENAME = "assets/sprites/heart2.png";
const string BALLOON_FILENAME = "assets/sprites/mainBalloon.png";
const string PREGNANT_FILENAME = "assets/sprites/cropped_heart_balloon.png";
const string TOWERS_FILENAME = "towers.csv";
const string MAP_FILENAME = "map.txt";

const string SCORE_BOARD_FONT_FILENAME = "assets/sprites/fonts/anton.ttf";
const string DESCRIBTION_FONT_FILENAME = "assets/sprites/fonts/PressStart2P.ttf";

const float BOMB_RADIUS = 30.f;

const int TOWER_COUNT = 3;
const string NORMAL_SHOOTER = "normal_shooter";
const string ICE_SHOOTER = "ice_shooter";
const string CANNON = "cannon";
const string NORMAL_SHOOTER_TITLE = "Fire Tower";
const string ICE_SHOOTER_TITLE = "Ice Tower";
const string CANNON_TITLE = "Cannon";

const float MAX_HEALTH = 40.f;
const int INITIAL_MONEY = 420;

const float ROTATION_SPEED = 135;

const float FREEZE_TIME = 1;


namespace t_info
{
    const int NAME = 0;
    const int PRICE = 1;
    const int RADIUS = 2;
    const int COOLDOWN = 3;
}

struct PlayerStats
{
    int round = 0;
    float health = MAX_HEALTH;
    int money = INITIAL_MONEY;
};

enum r_dir
{
    CW,
    CCW,
    ND
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

int generateRandom(int from, int to);

#endif // define CONSTS_HPP