#ifndef UI_HPP
#define UI_HPP

#include <SFML/Graphics.hpp>

#include <game/GameEventSystem.hpp>

using namespace sf;

/**
 * Клас для графічного інтерфейсу. Відокремив від ігрових об'єктів (GameObject)
 * бо потрібна більша гнучкість у використанні цього класу.
*/
class UI : public Drawable{
private:
    // TODO: move this data to PlayerData struct
    int score;
    float health;
    float damage;
    // END

    Font font;
    Text scoreText;

    RectangleShape hpBarBg;
    RectangleShape hpBarProgress;
public:
    UI();
    void draw(RenderTarget& target, RenderStates states) const;

};

#endif