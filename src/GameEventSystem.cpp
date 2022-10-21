#include <game/GameEventSystem.hpp>

#include <iostream>

GameEventSystem *GameEventSystem::instance = nullptr;

GameEventSystem::GameEventSystem() {}

GameEventSystem* GameEventSystem::getInstance() {
    if (instance == nullptr)
        instance = new GameEventSystem;
    return instance;
}

void GameEventSystem::on(std::string name, std::function<void(GameEvent*)> callback) {
    GameEventSystem::getInstance()->subscribers.push_back(std::pair(name, callback));
}

// Implement later
// void GameEventSystem::remove(std::string name) {}

void GameEventSystem::emit(GameEvent *event) {
    GameEventSystem::getInstance()->eventStack.push_back(event);
}

void GameEventSystem::update() {
    for (auto event : eventStack) {
        for (auto sub : subscribers) {
            if (event->name == sub.first)
                sub.second(event);
        }
        delete event;
    }
    eventStack.clear();
}