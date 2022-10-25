#include <game/GameRunner.hpp>

GameRunner* GameRunner::instance = nullptr;

GameRunner::GameRunner() {
    window = new RenderWindow(VideoMode(1280, 720, 32), "Asteroids");
    eventSystem = GameEventSystem::getInstance();
    viewUtil = ViewUtil::getInstance();
    levelManager = new LevelManager;
    ui = new UI;

    window->setFramerateLimit(240);
}

void GameRunner::init() {
    /* Initialize global events */
    GameEventSystem::on("ObjectSpawn", [](GameEvent *ev) {
        Logger::log("(GameRunner::init) Object spawned");

        ObjectEvent *event = static_cast<ObjectEvent*>(ev);
        addObject(event->obj);

        delete event;
        delete ev;
    });

    /* Initialize the player */
    auto player = new PlayerSpaceship;
    GameRunner::addObject(player);
}

GameRunner* GameRunner::Game() {
    if (instance == nullptr)
        instance = new GameRunner;

    return instance;
}

Window* GameRunner::getWindow() {
    return Game()->window;
}

bool isObjectFaraway(IGameObject *object) {
    auto pos = object->getTransformable().getPosition();
    return (pos.x >= 3000 || pos.x < -1000) && (pos.y >= 2000 || pos.y < -1000);
}

void GameRunner::updateObjects(float dt) {
    for (auto obj : objects.getActualVector()) {
        if (isObjectFaraway(obj))
            obj->setActive(false);

        if (obj->isActive())
            obj->update(dt);
    }
}

void GameRunner::drawObjects() {
    for (auto obj : objects.getActualVector())
        if (obj->isActive() && obj->isVisible())
            window->draw(*obj);

    window->draw(*ui);
}

void GameRunner::checkCollisions() {
    IGameObject *obj1, *obj2;
    float dist = 0, size = 0;

    for (int i = 0; i < objects.getSize(); i++) {
        obj1 = objects[i];

        if (!obj1->isActive())
            continue;

        for (int j = i + 1; j < objects.getSize(); j++) {
            obj2 = objects[j];

            // Same type collision skip optimization
            if (obj1->getTypeHash() == obj2->getTypeHash())
                continue;

            // Distance optimization
            // If distance between objects higher than size of obj
            // that skip iteration and go to next obj
            dist = Utils::magnitudeOf(obj1->getTransformable().getPosition() - obj2->getTransformable().getPosition());
            size = fmaxf(obj1->getMaxSize(), obj2->getMaxSize());
            
            if (!obj2->isActive() || dist > size)
                continue;

            if (obj1->getBounds().intersects(obj2->getBounds())) {
                obj1->onCollision(obj2);
                obj2->onCollision(obj1);

                Logger::log(LogLevel::ALERT, "(GameRunner::checkCollisions) Collision happen!");
            }
        }
    }
}

#include <memory>

void GameRunner::addObject(IGameObject *obj) {
    Logger::log(LogLevel::ERROR, "(GameRunner::addObject) Game add object");
    
    Game()->objects.push(obj);
    obj->init();
}

IGameObject* GameRunner::getObjectByIndex(int index) {
    return Game()->objects.getActualVector().at(index);
}

void GameRunner::run() {
    Clock clock;
    float dt = 0;
    float sec = 0;
    int fps = 0;

    while (window->isOpen()) {

        Event event;
        while (window->pollEvent(event)) {
            switch (event.type) {
                case Event::Closed:
                    Logger::save("log.txt");
                    window->close();
                    break;
            }
        }
        
        // ============== MAIN BODY ==============
        objects.block();

        updateObjects(dt);
        checkCollisions();
        levelManager->update();
        eventSystem->update();
                                    
        window->clear(Color::Black);

        drawObjects();

        window->display();

        objects.checkOptimization();
        objects.optimize();
        objects.flush();
        // ============ END MAIN BODY ============


        /* Calculate delta time (time of one frame) */
        dt = clock.getElapsedTime().asSeconds();
        clock.restart();
        
        /* Calculates FPS */
        if (sec < 1) {
            fps++;
            sec += dt;
        } else {
            window->setTitle("FPS: " + std::to_string(fps));
            sec = 0;
            fps = 0;
        }

        Logger::log("----------------------" + std::to_string(dt) + "s ----------------------");
    }
}