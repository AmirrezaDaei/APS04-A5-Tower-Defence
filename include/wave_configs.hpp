#ifndef WAVE_CONFIGS_HPP_INCLUDE
#define WAVE_CONFIGS_HPP_INCLUDE

#include <vector>
#include <map>
#include <string>
#include <utility>

using namespace std;

struct AttackWave {
    map<string, int> enemiesCount;
    pair<int, int> enemyLaunchGapMs;
};

const vector<AttackWave> ATTACKING_PLAN = {
    {{{{"Normal", 5}}}, {500, 700}},
    {{{{"Normal", 10}, {"Pregnant", 5}}}, {400, 600}},
    {{{{"Normal", 15}, {"Pregnant", 10}}}, {200, 400}}
};

const int WAVE_LAUNCH_GAP_SECS = 10;

#endif // WAVE_CONFIGS_HPP_INCLUDE