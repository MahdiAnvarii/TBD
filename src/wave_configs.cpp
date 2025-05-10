#include "wave_configs.h"
#include "utils.h"

WaveManager::WaveManager(const Map& gameMap, vector<Baloon>& baloonsRef)
    : map(gameMap), baloons(baloonsRef) {}

void WaveManager::update() {
    float currentTime = gameClock.getElapsedTime().asSeconds();

    if (!waveInProgress && currentWaveIndex < ATTACKING_PLAN.size() &&
        currentTime >= nextWaveStartTimeSec) {
        prepareNextWave();
    }

    if (waveInProgress && !pendingBalloons.empty()) {
        if (spawnClock.getElapsedTime().asMilliseconds() >= pendingBalloons.front().second) {
            spawnBalloon(pendingBalloons.front().first);
            pendingBalloons.erase(pendingBalloons.begin());
            spawnClock.restart();
        }
    }

    if (waveInProgress && pendingBalloons.empty()) {
        waveInProgress = false;
        nextWaveStartTimeSec = currentTime + WAVE_LAUNCH_GAP_SECS;
        currentWaveIndex++;
    }
}

void WaveManager::prepareNextWave() {
    const AttackWave& wave = ATTACKING_PLAN[currentWaveIndex];
    pendingBalloons.clear();

    for (const auto& [type, count] : wave.enemiesCount) {
        for (int i = 0; i < count; ++i) {
            int delay = rand() % (wave.enemyLaunchGapMs.second - wave.enemyLaunchGapMs.first + 1)
                      + wave.enemyLaunchGapMs.first;
            pendingBalloons.emplace_back(type, delay);
        }
    }

    random_shuffle(pendingBalloons.begin(), pendingBalloons.end());
    waveInProgress = true;
    spawnClock.restart();
    roundOFWave++;
}

void WaveManager::spawnBalloon(const string& type) {
    BaloonType btype = (type == "Normal") ? BaloonType::Simple : BaloonType::Pregnant;
    baloons.emplace_back(map.getTheMap(), map.getRoadMap(), btype);
}

int WaveManager::getRoundOfWave() const { return roundOFWave; }