#ifndef WAVES_CONFIG_HPP_INCLUDE
#define WAVES_CONFIG_HPP_INCLUDE

#include <map>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct AttackWave {
    map<string, int> enemies_count;
    pair<int, int> enemy_launch_gap_ms;
};

const vector<AttackWave> ATTACKING_PLAN = {
    {{{{"Normal", 5}}}, {500, 700}}, {{{{"Normal", 10}, {"Pregnant", 5}}}, {400, 600}}, {{{{"Normal", 15}, {"Pregnant", 10}}}, {200, 400}}};

const int WAVE_LAUNCH_GAP_SECS = 10;

#endif  // WAVE_CONFIGS_HPP_INCLUDE