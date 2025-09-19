#include "game.hpp"

Game::Game() {
    ifstream input(MAP_FILENAME);
    string line;
    vector<string> map;

    while (getline(input, line)) map.push_back(line);

    int map_height = map.size();
    int map_width = map[0].size();

    window.create(VideoMode((unsigned int)(TILE_SIZE * map_width + SHOP_WIDTH), (unsigned int)(TILE_SIZE * map_height)), "Blooooons Defence",
        Style::Titlebar | Style::Close);
    VideoMode desktop = VideoMode::getDesktopMode();
    window.setPosition(Vector2i((desktop.width - window.getSize().x) / 2, (desktop.height - window.getSize().y) / 2));
    readWaveConfigs();
    shared_ptr<TextureManager> texture_manager = make_shared<TextureManager>();
    sound_manager = make_shared<SoundManager>();
    game_map = make_shared<Map>(map_width, map_height, map, texture_manager, sound_manager, player_stats.money, player_stats.health);
    game_shop = make_shared<Shop>(texture_manager, window, player_stats.money);
    score_board = make_shared<ScoreBoard>(window);
    input.close();

    game_over_texture = texture_manager->getTexture(GAME_OVER_DISPLAY_FILENAME);
    Game_over_sprite.setTexture(game_over_texture);
    Game_over_sprite.setOrigin(game_over_texture.getSize().x / 2.0f, game_over_texture.getSize().y / 2.0f);
    Game_over_sprite.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    Game_over_sprite.scale(window.getSize().x / game_over_texture.getSize().x, window.getSize().y / game_over_texture.getSize().y);

    you_win_texture = texture_manager->getTexture(YOU_WIN_DISPLAY_FILENAME);
    you_win_sprite.setTexture(you_win_texture);
    you_win_sprite.setOrigin(you_win_texture.getSize().x / 2.0f, you_win_texture.getSize().y / 2.0f);
    you_win_sprite.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    you_win_sprite.scale(window.getSize().x / you_win_texture.getSize().x, window.getSize().y / you_win_texture.getSize().y);

    state = PLAYING;
}

void Game::updateWindow(float dt) {
    game_map->drawTiles(window);
    game_map->drawTowers(window, dt);
    game_map->drawBalloons(window, dt);
    score_board->drawScoreBoard(window, player_stats);
    game_shop->drawShop(window);
}

void Game::run() {
    // dige ina ro comment nagir bekhoda baraye neshun dadane!!
    // if (!music.openFromFile(KOKALAK_MUSIC_FILENAME))
    //     cerr << "Unable to load music file" << endl;
    if (!music.openFromFile(NAMELESS_KING_MUSIC_FILENAME)) cerr << "Unable to load music file" << endl;
    if (!win.openFromFile(DR_STOP_SOUND_FILENAME)) cerr << "Unable to load music file" << endl;
    if (!lose.openFromFile(YOU_DIED_SOUND_FILENAME)) cerr << "Unable to load music file" << endl;
    music.setLoop(true);
    music.play();
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (state == PLAYING) {
                if (event.type == Event::MouseButtonPressed) {
                    if (event.mouseButton.button == Mouse::Left) {
                        Vector2i mousePos = Mouse::getPosition(window);
                        chosen_tower = game_shop->handleBuyingTower(mousePos);
                        if (chosen_tower != NULL) {
                            bool bought = game_map->plantTower(mousePos, chosen_tower);
                            if (bought == true) {
                                player_stats.money -= chosen_tower->getPrice();
                                game_shop->abortBuying();
                            }
                            chosen_tower = nullptr;
                        }
                    }
                    if (event.mouseButton.button == Mouse::Right) {
                        chosen_tower = nullptr;
                        game_shop->abortBuying();
                    }
                }
            }
        }
        if (state == PLAYING) {
            float dt = clock.restart().asSeconds();
            Vector2i mouse_pos = Mouse::getPosition(window);
            handleWave(dt);
            game_shop->handleTowerBeingHovered(mouse_pos);
            game_map->handleTowersAiming();
            window.clear();
            if (player_stats.health <= 0) {
                state = GAME_OVER;
                music.pause();
                continue;
            }
            updateWindow(dt);
            window.display();
            if (player_stats.round == ATTACKING_PLAN.size() && game_map->isBalloonsPopped() && is_wave_active == false) {
                clock.restart();
                state = GAME_WON;
                music.pause();
            }
        }

        if (state == GAME_OVER) {
            window.clear();
            window.draw(Game_over_sprite);
            window.display();
            if (!hasPlayedLoseMusic) {
                lose.play();
                hasPlayedLoseMusic = true;
            }
        }
        if (state == GAME_WON)
            if (clock.getElapsedTime().asSeconds() > WAITING_TIME) {
                window.clear();
                window.draw(you_win_sprite);
                window.display();
                if (!hasPlayedWinMusic) {
                    win.play();
                    hasPlayedWinMusic = true;
                }
            }
    }
}

void Game::handleWave(float dt) {
    waves_time_gap += dt;
    if (is_wave_active) {
        balloons_time_gap += dt;
        if (balloons_time_gap >= gap) generateRandomBalloon();
        if (pregnants_spawned >= waves_config[player_stats.round - 1].pregnant_count &&
            normals_spawned >= waves_config[player_stats.round - 1].normal_count)
            endWave();
    } else {
        waves_time_gap += dt;
        if (waves_time_gap >= WAVE_LAUNCH_GAP_SECS)
            if (player_stats.round < ATTACKING_PLAN.size() && game_map->isBalloonsPopped()) startNewWave();
    }
}

void Game::spawnNormal() {
    normals_spawned++;
    game_map->constructNormal(game_map->getStartPoint(), game_map->getStartVDir());
    balloons_time_gap = 0.f;
}

void Game::spawnPregnant() {
    pregnants_spawned++;
    game_map->constructPregnant(game_map->getStartPoint(), game_map->getStartVDir());
    balloons_time_gap = 0.f;
}

void Game::startNewWave() {
    player_stats.round++;
    waves_time_gap = 0.f;
    is_wave_active = true;
    pregnants_spawned = 0;
    normals_spawned = 0;
}

void Game::endWave() {
    is_wave_active = false;
    waves_time_gap = 0.f;
}

void Game::generateRandomBalloon() {
    if (generateRandom(1, 2) == 1) {
        if (pregnants_spawned < waves_config[player_stats.round - 1].pregnant_count) spawnPregnant();
    } else {
        if (normals_spawned < waves_config[player_stats.round - 1].normal_count) spawnNormal();
    }
    gap = float(generateRandom(waves_config[player_stats.round - 1].min_gap_ms, waves_config[player_stats.round - 1].max_gap_ms)) / TO_SECONDS;
}

void Game::readWaveConfigs() {
    for (const AttackWave &wave : ATTACKING_PLAN) {
        WaveConfig config;
        for (const auto &enemy : wave.enemies_count) {
            if (enemy.first == "Normal")
                config.normal_count = enemy.second;
            else if (enemy.first == "Pregnant")
                config.pregnant_count = enemy.second;
        }
        config.min_gap_ms = wave.enemy_launch_gap_ms.first;
        config.max_gap_ms = wave.enemy_launch_gap_ms.second;
        waves_config.push_back(config);
    }
}
