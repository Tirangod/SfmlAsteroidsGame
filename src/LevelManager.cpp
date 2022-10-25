#include <game/LevelManager.hpp>

LevelManager::LevelManager() {
    clock.restart();
    
    wavesDelay = 5;
    baseEnemyNumber = 15;
    difficulty = 1;
    waveNum = 0;
}

void LevelManager::update() {
    if (clock.getElapsedTime().asSeconds() >= wavesDelay) {
        clock.restart();
        genWave();
    }
}

void LevelManager::genWave() {
    Logger::log("(LevelManager::genWave) New wave generated");

    Vector2u target(1280, 720);
    Vector2f center(target.x/2, target.y/2);

    int total = baseEnemyNumber * difficulty;
    float rad = (2 * Utils::PI) / total;
    float dist = 0;
    float speed =  50.f * sqrtf(difficulty);

    for (int i = 0; i < total; i++) {
        auto pos = Vector2f(sin(rad * i), cos(rad * i)) * dist + center;
        auto dir = center - pos;
        dist = 600.f + 200.f * Utils::rand() * Utils::randSign();
        Utils::normalize(dir);

        auto asteroid = new Asteroid(pos, dir, speed);
        GameEventSystem::emit(new ObjectEvent("ObjectSpawn", asteroid));
    }

    difficulty++;
    wavesDelay *= 1.5f;
}