#ifndef GAMERUNNER_HPP
#define GAMERUNNER_HPP

#include <iostream>
#include <vector>
#include <cmath>

#include <SFML/Graphics.hpp>

#include <game/PlayerSpaceship.hpp>
#include <game/GameEventSystem.hpp>
#include <game/GameObjectsList.hpp>
#include <game/LevelManager.hpp>
#include <game/IGameObject.hpp>
#include <game/GameEvent.hpp>
#include <game/ViewUtil.hpp>
#include <game/Asteroid.hpp>
#include <game/Logger.hpp>
#include <game/Utils.hpp>
#include <game/UI.hpp>

using namespace sf;

class GameRunner {

private:
    static GameRunner *instance;

    GameObjectsList objects;

    RenderWindow *window; // TODO: Probably should be not a pointer
    ViewUtil *viewUtil;
    GameEventSystem *eventSystem;
    LevelManager *levelManager; // TODO: Probably should be singleton
    UI *ui; // TODO: Probably should be not a pointer

    GameRunner();
    
    void updateObjects(float dt);
    void drawObjects();
    void checkCollisions();

public:
    static GameRunner* Game();
    static Window* getWindow();

    static void addObject(IGameObject *obj);
    static IGameObject* getObjectByIndex(int index);

    void init();
    void run();

    GameRunner(GameRunner &game) = delete;
    void operator=(GameRunner&) = delete;
};

#endif