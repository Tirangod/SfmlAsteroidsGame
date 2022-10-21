#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <SFML/System.hpp>

using namespace sf;

class ViewUtil {
private:
    static ViewUtil *instance;

    Vector2i viewSize;

    ViewUtil();
public:
    static ViewUtil* getInstance();
    static bool isOutOfViewUtil(Vector2f vec); 

    void setSizeInfo(Vector2i size);

    ViewUtil(ViewUtil &game) = delete;
    void operator=(ViewUtil&) = delete;
};

#endif