#ifndef LEVELMANAGER_HPP
#define LEVELMANAGER_HPP

#include <cmath>

#include <SFML/System.hpp>

#include <game/GameEventSystem.hpp>
#include <game/Asteroid.hpp>
#include <game/Logger.hpp>

class LevelManager {
private:
    sf::Clock clock;
    float wavesDelay;
    int baseEnemyNumber;
    int difficulty;
    int waveNum;
public:
    LevelManager();
    
    void genWave();
    void update();
};

#endif