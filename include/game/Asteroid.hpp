#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include <cmath>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <game/GameEventSystem.hpp>
#include <game/IGameObject.hpp>
#include <game/Bullet.hpp>
#include <game/Logger.hpp>
#include <game/Utils.hpp>

using namespace sf;

class Asteroid : public IGameObject {
private:
    long hash;
    
    Image image;
    Texture texture;
    Sprite sprite;

    Vector2f moveDir;
    float speed;

    bool _isActive;
    bool _isVisible;
    
    RectangleShape rect;
public:
    ~Asteroid();
    Asteroid(Vector2f pos, Vector2f dir);

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