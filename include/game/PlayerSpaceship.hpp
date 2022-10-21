#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cmath>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <game/IGameObject.hpp>
#include <game/GameRunner.hpp>
#include <game/GameEvent.hpp>
#include <game/Bullet.hpp>
#include <game/Logger.hpp>
#include <game/Utils.hpp>

using namespace sf;

class PlayerSpaceship : public IGameObject
{

private:
    long hash;
    
    Image image;
    Texture texture;
    Sprite sprite;

    Vector2f moveDir;
    float speed;

    bool _isActive;
    bool _isVisible;

    bool isShooting;
    int shootingTimes;
    int shootingDelay;
    
    void moving(float dt);
    void rotation();
    void shooting();
    void onShot();

public:
    PlayerSpaceship();

    void onCollision(IGameObject *other);
    void init();
    void update(float dt);
    void draw(RenderTarget &target, RenderStates states) const;
    Transformable getTransformable();
    FloatRect getBounds();
    float getMaxSize();
    void setActive(bool flag);
    bool isActive();
    bool isVisible();
    long getTypeHash();
};

#endif