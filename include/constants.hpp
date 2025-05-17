#ifndef CONSTS_HPP
#define CONSTS_HPP

#include <iostream>
#include <random>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;

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

const string GAME_OVER_DISPLAY_FILENAME = "assets/sprites/game_over.png";
const string YOU_WIN_DISPLAY_FILENAME = "assets/sprites/you_win.png";
const string MUSIC_FILENAME = "assets/music & soundTracks/Zang_Bzn_Ambulaance.ogg";
const string BUILDABLE_TILE_FILENAME = "assets/sprites/extra_sprite/tiles/buildable_tile.png";
const string PATH_TILE_FILENAME = "assets/sprites/extra_sprite/tiles/path_tile.png";
const string SHOOTERS_FILEPATH = "assets/sprites/";
const string HEART_FILENAME = "assets/sprites/heart2.png";
const string BALLOON_FILENAME = "assets/sprites/mainBalloon.png";
const string PREGNANT_FILENAME = "assets/sprites/cropped_heart_balloon.png";
const string ICE_RAY_FILENAME = "assets/sprites/extra_sprite/projectiles/ice_ray2.png";
const string FIRE_RAY_FILENAME = "assets/sprites/extra_sprite/projectiles/fire_ray.png";
const string CANNON_RAY_FILENAME = "assets/sprites/extra_sprite/projectiles/cannon_ray.png";
const string RED_NORMAL_BALLOON_FILENAME = "assets/sprites/RedNormalBalloon.png";
const string FROZEN_NORMAL_BALLOON_FILENAME = "assets/sprites/FrozenNormalBalloon.png";
const string PURPLE_NORMAL_BALLOON_FILENAME = "assets/sprites/PurpleNormalBalloon.png";
const string PREGNANT_BALLOON_FILENAME = "assets/sprites/PregnantBalloon.png";
const string FROZEN_PREGNANT_BALLOON_FILENAME = "assets/sprites/FrozenPregnantBalloon.png";
const string TOWERS_FILENAME = "towers.csv";
const string MAP_FILENAME = "map.txt";
const string SCORE_BOARD_FONT_FILENAME = "assets/sprites/fonts/anton.ttf";
const string DESCRIBTION_FONT_FILENAME = "assets/sprites/fonts/PressStart2P.ttf";
const string LASER_SOUND_FILENAME = "assets/music & soundTracks/laser-sound-fx_B_major.wav";
const string EXPLOSION_SOUND_FILENAME = "assets/music & soundTracks/smoke-bomb-6761.ogg";
const string BALLOON_POP_SOUND_FILENAME = "assets/music & soundTracks/balloon-pop-ni-sound-1-00-01.ogg";
const string BALLOON_FREEZE_SOUND_FILENAME = "assets/music & soundTracks/ice-cracking-01 (mp3cut.net).ogg";

const float BOMB_RADIUS = 40.f;

const int TOWER_COUNT = 3;
const string NORMAL_SHOOTER = "normal_shooter";
const string ICE_SHOOTER = "ice_shooter";
const string CANNON = "cannon";
const string NORMAL_SHOOTER_TITLE = "Fire Tower";
const string ICE_SHOOTER_TITLE = "Ice Tower";
const string CANNON_TITLE = "Cannon";

const float MAX_HEALTH = 20.f;
const int INITIAL_MONEY = 100;
const float DAMAGE = 2;
const float ROTATION_SPEED = 200;
const int TO_SECONDS = 1000;
const float FREEZE_TIME = 1;
const int POINT = 20;


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


struct WaveConfig {
    int normal_count = 0;
    int pregnant_count = 0;
    int min_gap_ms;
    int max_gap_ms;
};

enum BalloonType {
    PREGNANT,
    NORMAL
};

enum r_dir
{
    CW,
    CCW,
    ND
};

enum GameState
{
    PLAYING,
    GAME_WON,
    GAME_OVER
}; 

int generateRandom(int from, int to);
void loadSound(Sound& sound, string filename);

#endif // define CONSTS_HPP