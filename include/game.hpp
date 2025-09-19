#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include <memory>
#include <soundmanager.hpp>
#include <vector>

#include "balloon.hpp"
#include "constants.hpp"
#include "map.hpp"
#include "scoreboard.hpp"
#include "shop.hpp"
#include "tile.hpp"
#include "waves_config.hpp"

using namespace std;

class Game {
public:
    Game();
    void run();

private:
    Music music;
    Music win;
    Music lose;
    bool hasPlayedLoseMusic = false;
    bool hasPlayedWinMusic = false;
    void updateWindow(float dt);
    void handleWave(float dt);
    void spawnNormal();
    void spawnPregnant();
    void startNewWave();
    void generateRandomBalloon();
    void endWave();
    void readWaveConfigs();
    Clock clock;
    float waves_time_gap = 0.f;
    float balloons_time_gap = 0.f;
    float gap = 0;
    int normals_spawned = 0;
    int pregnants_spawned = 0;
    bool is_wave_active = false;
    vector<WaveConfig> waves_config;
    shared_ptr<Map> game_map;
    shared_ptr<Shop> game_shop;
    shared_ptr<ScoreBoard> score_board;
    shared_ptr<SoundManager> sound_manager;
    RenderWindow window;
    PlayerStats player_stats;
    GameState state;
    shared_ptr<ShopTower> chosen_tower = nullptr;
    Texture game_over_texture;
    Sprite Game_over_sprite;
    Texture you_win_texture;
    Sprite you_win_sprite;
};

#endif  // define GAME_HPP