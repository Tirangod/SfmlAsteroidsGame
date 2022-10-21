#include <game/Asteroid.hpp>

Asteroid::~Asteroid() { 
    GameEventSystem::emit(new GameEvent("ScoreIncrement"));
    Logger::log("(Asteroid::~) Asteroid destroyed"); 
}

Asteroid::Asteroid(Vector2f pos, Vector2f dir) : moveDir(Utils::normalize(dir)) {
    hash = Utils::hashOf("Asteroid");
    _isActive = true;
    _isVisible = true;
    
    image.loadFromFile("assets/asteroid.png");
    image.createMaskFromColor(Color::Black);
    texture.loadFromImage(image);

    float hw = sprite.getLocalBounds().width / 2; // Half width
    float hh = sprite.getLocalBounds().height / 2; // Half height

    sprite.setPosition(pos);
    sprite.setScale(1.5f, 1.5f);
    sprite.setTexture(texture);
    sprite.setOrigin(hw, hh);
    
    moveDir.x = 0;
    moveDir.y = 0;
    speed = 50.f;

    rect.setSize({hw*2, hh*2});
    rect.setOrigin(hw, hh);
    //rect.setFillColor(Color::Transparent);
    rect.setOutlineColor(Color::Green);
    rect.setOutlineThickness(2.f);
}

void Asteroid::init() { }

void Asteroid::update(float dt) {
    sprite.move(moveDir * speed * dt);
    rect.setPosition(sprite.getPosition());
}

void Asteroid::draw(RenderTarget &target, RenderStates states) const {
    target.draw(rect);
    target.draw(sprite);
}

void Asteroid::onCollision(IGameObject *other) {
    if (other->getTypeHash() == Utils::hashOf("Bullet")) {
        _isActive = false;
    }
}

Transformable Asteroid::getTransformable() { return sprite; }

FloatRect Asteroid::getBounds() { return sprite.getGlobalBounds(); }

float Asteroid::getMaxSize() { return fmaxf(getBounds().width, getBounds().height); }

void Asteroid::setActive(bool flag) { _isActive = flag; }

bool Asteroid::isActive() { return _isActive; }

bool Asteroid::isVisible() { return _isVisible; }

long Asteroid::getTypeHash() { return hash; }

