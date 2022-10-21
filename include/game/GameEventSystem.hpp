#ifndef GAMEEVENTSYSTEM_HPP
#define GAMEEVENTSYSTEM_HPP

#include <string>
#include <vector>
#include <utility>
#include <functional>

#include <game/GameEvent.hpp>

class GameEventSystem {

private:
    static GameEventSystem *instance;

    std::vector<GameEvent*> eventStack;
    std::vector<std::pair<std::string, std::function<void(GameEvent*)>>> subscribers;
    
    GameEventSystem();

public:
    static GameEventSystem* getInstance();
    
    // Subscribes on certain event
    static void on(std::string name, std::function<void(GameEvent*)> callback);

    // Emits certain event
    static void emit(GameEvent *event);

    // TODO
    // static void emitOnce(GameEvent *event);

    void update();

    GameEventSystem(GameEventSystem &game) = delete;
    void operator=(GameEventSystem&) = delete;
};

#endif
