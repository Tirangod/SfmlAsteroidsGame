#include <game/Bullet.hpp>

Bullet::Bullet(Vector2f pos, Vector2f v) : moveDir(v) {
    hash = Utils::hashOf("Bullet");
    _isActive = true;
    _isVisible = true;
    
    image.loadFromFile("assets/bullet.png");
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setScale(0.2f, 1);
    sprite.setPosition(pos);
    sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);

    moveDir.x = 0;
    moveDir.y = 0;
    speed = 350.0;
    
    float angle = Utils::radToDeg(atan2f(v.x, v.y));
    
    sprite.setRotation(-angle);
}

void Bullet::init() { }

void Bullet::update(float dt) {
    sprite.move(moveDir * speed * dt);

    /*
    if (GameRunner::isPointOut(sprite.getPosition()))
        _isActive = false;
    */
}

void Bullet::draw(RenderTarget &target, RenderStates states) const {
    target.draw(sprite);
}

void Bullet::onCollision(IGameObject *other) {
    if (other->getTypeHash() == Utils::hashOf("Asteroid")) {
        //_isActive = false;
    }
}

void Bullet::setActive(bool flag) { _isActive = flag; }

Transformable Bullet::getTransformable() { return sprite; }

bool Bullet::isActive() { return _isActive; }

bool Bullet::isVisible() { return _isVisible; }

FloatRect Bullet::getBounds() { return sprite.getGlobalBounds(); }

float Bullet::getMaxSize() { return fmaxf(getBounds().width, getBounds().height); }

long Bullet::getTypeHash() { return hash; }

