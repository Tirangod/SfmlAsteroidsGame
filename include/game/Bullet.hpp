#ifndef BULLET_HPP
#define BULLET_HPP

#include <cmath>

#include <SFML/Graphics.hpp>

#include <game/IGameObject.hpp>
#include <game/Asteroid.hpp>
#include <game/Utils.hpp>

using namespace sf;

class Bullet : public IGameObject {
private:
    long hash;
    
    Image image;
    Texture texture;
    Sprite sprite;

    Vector2f moveDir;
    float speed;

    bool _isActive;
    bool _isVisible;
public:
    Bullet(Vector2f pos, Vector2f v);
    
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