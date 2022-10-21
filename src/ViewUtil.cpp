#include <game/ViewUtil.hpp>

ViewUtil *ViewUtil::instance = nullptr;

ViewUtil::ViewUtil() {}

ViewUtil* ViewUtil::getInstance() {
    if (instance == nullptr)
        instance = new ViewUtil;
    return instance;
}

bool ViewUtil::isOutOfViewUtil(Vector2f vec) {
    return (vec.x > instance->viewSize.x || vec.x < 0) && (vec.y > instance->viewSize.y  || vec.y < 0);
}


void ViewUtil::setSizeInfo(Vector2i size) {
    viewSize = size;
}