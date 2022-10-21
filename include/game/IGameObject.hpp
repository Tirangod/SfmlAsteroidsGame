#ifndef IGAMEOBJECT_HPP
#define IGAMEOBJECT_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace sf;

/**
 * Клас (інтерфейс), який є базовим для ігрових об'єктів
 * таких, як: астероїди, кулі, уламки. Все що об'єднано
 * спільною поведінкою (відображення на екрані та ігрова логіка)
 */
class IGameObject : public Drawable
{
public:
    virtual void onCollision(IGameObject *other) = 0;
    virtual void init() = 0;
    virtual void update(float dt) = 0;
    virtual bool isActive() = 0;
    virtual bool isVisible() = 0;
    virtual void setActive(bool flag) = 0;
    virtual Transformable getTransformable() = 0;
    virtual FloatRect getBounds() = 0;
    virtual long getTypeHash() = 0; 
    virtual float getMaxSize() = 0;
    virtual void draw(RenderTarget &target, RenderStates states) const = 0;
};

#endif