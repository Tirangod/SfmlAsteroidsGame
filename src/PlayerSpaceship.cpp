#include <game/PlayerSpaceship.hpp>

PlayerSpaceship::PlayerSpaceship() {
    hash = Utils::hashOf("PlayerSpaceship");
    _isActive = true;
    _isVisible = true;

    image.loadFromFile("assets/spaceship.png");
    image.createMaskFromColor(Color::Black);

    texture.loadFromImage(image);

    sprite.setPosition(GameRunner::getWindow()->getSize().x/2, GameRunner::getWindow()->getSize().y/2);
    sprite.setTexture(texture);
    sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
    sprite.setScale(1.3f, 1.3f);

    moveDir.x = 0;
    moveDir.y = 0;
    speed = 400.f;

    isShooting = false;
    shootingCooldown = 0.f;
    shootingDelay = 20.f;
}

void PlayerSpaceship::init() {}

void PlayerSpaceship::moving(float dt) {
    bool w = Keyboard::isKeyPressed(Keyboard::W);
    bool s = Keyboard::isKeyPressed(Keyboard::S);
    bool a = Keyboard::isKeyPressed(Keyboard::A);
    bool d = Keyboard::isKeyPressed(Keyboard::D);

    if (w)
        moveDir.y = -1;
    else if (s)
        moveDir.y = 1;
    else
        moveDir.y = 0;

    if (a)
        moveDir.x = -1;
    else if (d)
        moveDir.x = 1;
    else
        moveDir.x = 0;

    Utils::normalize(moveDir);

    sprite.move(moveDir * speed * dt);
}

void PlayerSpaceship::onShot() {
    auto vec1 = sprite.getPosition();
    auto vec2 = Mouse::getPosition(*GameRunner::getWindow());
    auto diff = Vector2f(vec2.x - vec1.x, vec2.y - vec1.y);

    Utils::normalize(diff);

    float bso = 50.f; // Bullet Spawn Offset

    auto bullet = new Bullet(sprite.getPosition() + diff * bso, diff);
    GameRunner::addObject(bullet);
    
    Logger::log(LogLevel::INFO, "(Player::onShot) Player shot");
}

void PlayerSpaceship::shooting(float dt) {
    isShooting = Mouse::isButtonPressed(Mouse::Left);

    if (isShooting) {
        if (shootingCooldown >= shootingDelay) {
            shootingCooldown = 0;
            onShot();
        }
        shootingCooldown += 250.f * dt; // Remove magic constant
    } else {
        shootingCooldown = 0;
    }
}

void PlayerSpaceship::rotation() {
    auto vec1 = sprite.getPosition();
    auto vec2 = Mouse::getPosition(*GameRunner::getWindow());

    float angle = Utils::radToDeg(
        atan2f(
            vec1.y - vec2.y,
            vec1.x - vec2.x
            )
        );

    if (angle < 0)
        angle = 360 + angle;
    
    sprite.setRotation(angle + 180);
}

void PlayerSpaceship::update(float dt) {
    moving(dt);
    rotation();
    shooting(dt);
}

void PlayerSpaceship::draw(RenderTarget &target, RenderStates states) const {
    target.draw(sprite, states);
}

void PlayerSpaceship::onCollision(IGameObject *other) {

}

Transformable PlayerSpaceship::getTransformable() { return sprite; }

FloatRect PlayerSpaceship::getBounds() { return sprite.getGlobalBounds(); }

float PlayerSpaceship::getMaxSize() { return fmaxf(getBounds().width, getBounds().height); }

void PlayerSpaceship::setActive(bool flag) { _isActive = flag; }

bool PlayerSpaceship::isActive() { return _isActive; }

bool PlayerSpaceship::isVisible() { return _isVisible; }

long PlayerSpaceship::getTypeHash() { return hash; }
