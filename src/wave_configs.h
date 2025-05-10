#ifndef WAVE_CONFIGS_HPP
#define WAVE_CONFIGS_HPP

#include "utils.h"
#include "map.h"
#include "baloon.h"

struct AttackWave {
    map<string, int> enemiesCount;
    pair<int, int> enemyLaunchGapMs;
};

const vector<AttackWave> ATTACKING_PLAN = {
    {{{"Normal", 5}}, {500, 700}},
    {{{"Normal", 10}, {"Pregnant", 5}}, {400, 600}},
    {{{"Normal", 15}, {"Pregnant", 10}}, {200, 400}}
};

const int WAVE_LAUNCH_GAP_SECS = 10;

class WaveManager {
public:
    WaveManager(const Map& gameMap, std::vector<Baloon>& baloonsRef);
    void update();
    int getRoundOfWave() const;
private:
    const Map& map;
    vector<Baloon>& baloons;
    Clock gameClock;
    Clock spawnClock;
    int currentWaveIndex = 0;
    int roundOFWave = 0;
    float nextWaveStartTimeSec = WAVE_LAUNCH_GAP_SECS;
    bool waveInProgress = false;
    vector<pair<string, int>> pendingBalloons;

    void prepareNextWave();
    void spawnBalloon(const string& type);
};

#endif // WAVE_CONFIGS_HPP
