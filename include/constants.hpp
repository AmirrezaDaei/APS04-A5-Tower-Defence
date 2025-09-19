#ifndef CONSTS_HPP
#define CONSTS_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
using namespace std;
using namespace sf;

const float TILE_SIZE = 75.f;
const float TOWER_SIZE = 65.f;
const float HEART_SIZE = 40.f;
const float HEALTHBAR_LENGTH = 160.f;
const float HEALTHBAR_WIDTH = 20.f;
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
const string KOKALAK_MUSIC_FILENAME = "assets/music & soundTracks/Zang_Bzn_Ambulaance.ogg";
const string NAMELESS_KING_MUSIC_FILENAME = "assets/music & soundTracks/Nameless King .ogg";
const string YOU_DIED_SOUND_FILENAME =
    "assets/music & soundTracks/dark-souls--you-died--sound-effect-made-with-Voicemod.ogg";
const string DR_STOP_SOUND_FILENAME = "assets/music & soundTracks/dr-stop-2.ogg";
const string BUILDABLE_TILE_FILENAME = "assets/sprites/buildable_tile.png";
const string PATH_TILE_FILENAME = "assets/sprites/path_tile.png";
const string SHOOTERS_FILEPATH = "assets/sprites/";
const string HEART_FILENAME = "assets/sprites/heart2.png";
const string BALLOON_FILENAME = "assets/sprites/mainBalloon.png";
const string PREGNANT_FILENAME = "assets/sprites/cropped_heart_balloon.png";
const string ICE_RAY_FILENAME = "assets/sprites/ice_ray2.png";
const string FIRE_RAY_FILENAME = "assets/sprites/fire_ray.png";
const string CANNON_RAY_FILENAME = "assets/sprites/cannon_ray.png";
const string RED_NORMAL_BALLOON_FILENAME = "assets/sprites/RedNormalBalloon.png";
const string FROZEN_NORMAL_BALLOON_FILENAME = "assets/sprites/FrozenNormalBalloon.png";
const string PURPLE_NORMAL_BALLOON_FILENAME = "assets/sprites/PurpleNormalBalloon.png";
const string POPPED_NORMAL_BALLOON_FILENAME = "assets/sprites/popped_balloon.png";
const string POPPED_PURPLE_BALLOON_FILENAME = "assets/sprites/purple_popped_balloon.png";
const string PREGNANT_BALLOON_FILENAME = "assets/sprites/PregnantBalloon.png";
const string EXPLOSION_IMAGE_FILENAME = "assets/sprites/explosion_img.png";
const string FROZEN_PREGNANT_BALLOON_FILENAME = "assets/sprites/FrozenPregnantBalloon.png";
const string TOWERS_FILENAME = "towers.csv";
const string MAP_FILENAME = "map.txt";
const string SCORE_BOARD_FONT_FILENAME = "assets/fonts/anton.ttf";
const string DESCRIBTION_FONT_FILENAME = "assets/fonts/PressStart2P.ttf";
const string LASER_SOUND_FILENAME = "assets/music & soundTracks/laser-sound-fx_B_major.wav";
const string EXPLOSION_SOUND_FILENAME = "assets/music & soundTracks/explosion-80108.wav";
const string BALLOON_FREEZE_SOUND_FILENAME =
    "assets/music & soundTracks/ice-cracking-01 (mp3cut.net).ogg";
const string BALLOON_POP_SOUND_FILENAME = "assets/music & soundTracks/balloon-burst-383750.wav";

const float BOMB_RADIUS = 50.f;
const float BALLOON_SPEED = TILE_SIZE * 2;

const int TOWER_COUNT = 3;
const string NORMAL_SHOOTER = "normal_shooter";
const string ICE_SHOOTER = "ice_shooter";
const string CANNON = "cannon";
const string NORMAL_SHOOTER_TITLE = "Fire Tower";
const string ICE_SHOOTER_TITLE = "Ice Tower";
const string CANNON_TITLE = "Cannon";

const float MAX_HEALTH = 100.f;
const int INITIAL_MONEY = 2000;
const float DAMAGE = 2;
const float ROTATION_SPEED = 300;
const int TO_SECONDS = 1000;
const float FREEZE_TIME = 1;
const float POP_TIME = 0.1f;
const float RAY_SHOWING_TIME = 0.2f;
const float WAITING_TIME = 2;
const int POINT = 20;

const Color RADIUS_COLOR = Color(173, 216, 230, 50);
const Color BOMB_RADIUS_COLOR = Color(255, 0, 0, 128);
const Color UNAVAILBLE_TOWER_COLOR = Color(80, 80, 80);
const Color DESCRIPTION_COLOR = Color(63, 73, 142);
const Color BACKGROUND_COLOR = Color(200, 200, 200);
const Color SCOREBOARD_COLOR = Color(238, 204, 91);
const Color HB_BACKGROUND_COLOR = Color(211, 211, 211);
const Color HB_COLOR = Color(144, 238, 144);

const int DESCRIPTION_OUTLINE = -8;
const int HIGHLIGHT_OUTLINE = -3;
const int SCOREBOARD_OUTLINE = -5;
const int HB_OUTLINE = 3;

namespace t_info {
const int NAME = 0;
const int PRICE = 1;
const int RADIUS = 2;
const int COOLDOWN = 3;
}  // namespace t_info

struct PlayerStats {
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

enum BalloonType { PREGNANT, NORMAL };

enum BalloonState { FROZEN, NORMAL_STATE, DESTROYED, POPPED };

enum r_dir { CW, CCW, ND };

enum GameState { PLAYING, GAME_WON, GAME_OVER };

int generateRandom(int from, int to);
void createText(Text &text, Font &font, int size, Color color);

#endif  // define CONSTS_HPP