#ifndef GAMEEVENT_HPP
#define GAMEEVENT_HPP

#include <string>

#include <SFML/Graphics.hpp>

#include <game/IGameObject.hpp>

struct GameEvent {
    std::string name;
    GameEvent(std::string name) : name(name) {}
};

struct ObjectEvent : GameEvent {
    IGameObject *obj;
    ObjectEvent(std::string name, IGameObject *obj) : obj(obj), GameEvent(name) { }
};

#endif