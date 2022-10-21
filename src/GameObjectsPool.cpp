#include <game/GameObjectsPool.hpp>

GameObjectsPool::GameObjectsPool() {
    needToOptimize = false;
    needToFlush = false;
    canPushDirect = true;
}

void GameObjectsPool::block() { 
    canPushDirect = false; 

    /*
    std::string str = "(GameObjectsPool::block) Pushing is blocked:";
    str.append("\n\tIs need to flush: ").
        append(needToFlush ? "true" : "false");
    Logger::log(str);
    */
}

void GameObjectsPool::checkOptimization() {
    for (auto obj : actualVector) {
        if (!obj->isActive()) {
            needToOptimize = true;
            return;
        }
    }
    needToOptimize = false;
}

void GameObjectsPool::optimize() {

    if (!needToOptimize)
        return;

    int num = 0; // Optimized objects number

    /* VERSION 0
    */
    IGameObject *objBuffer;
    
    std::vector<IGameObject*> vecBuffer;
    vecBuffer.reserve(actualVector.size());

    for (int i = 0; i < getSize(); i++) {
        objBuffer = this->at(i);

        // If object isnt active, so that it need to be deleted
        if (!objBuffer->isActive()) {
            num++;
            delete this->at(i);
            continue;
        }

        vecBuffer.push_back(objBuffer);
    }
    
    actualVector.clear();

    for (int i = 0; i < vecBuffer.size(); i++) {
        // push(vecBuffer[i]);
        directPush(vecBuffer[i]); // more performant
    }

    vecBuffer.clear();

    /* VERSION 1
    for (auto it = actualVector.begin(); it < actualVector.end(); it++) {
        if ((*it)->isActive())
            continue;
        
        // Else it isnt active
        actualVector.erase(it);
        num++;
    }

    */
    Logger::log("(GameObjectsPool::optimize) List optimized: " + std::to_string(num));
}

void GameObjectsPool::set(IGameObject *obj, int index) {
    actualVector[index] = obj;
}

void GameObjectsPool::push(IGameObject* object) {
    if (canPushDirect) {
        Logger::log("(GameObjectsPool::push) Push object DIRECTLY");
        actualVector.push_back(object);
    } else {
        Logger::log("(GameObjectsPool::push) Push object to BUFFER");
        bufferedVector.push_back(object);
        needToFlush = true;
    }
}

void GameObjectsPool::directPush(IGameObject* object) { 
    actualVector.push_back(object);
}

int GameObjectsPool::flush() {
    canPushDirect = true;
    
    if (!needToFlush)
        return 0;

    for (auto obj : bufferedVector) {
        actualVector.push_back(obj);
    }

    int bv_size = bufferedVector.size(); // Buffered vector size
    bufferedVector.clear();

    needToFlush = false;

    //============ LOGGING ============
    std::string str = "(GameObjectsPool::flush) Flushed from buffer:";
    str.append("\n\tFlush buffer was: " + std::to_string(bv_size)).
        append("\n\tActual vector size: " + std::to_string(actualVector.size())).
        append("\n\tBuffered vector size: " + std::to_string(bufferedVector.size()));
    Logger::log(str);
    //========== END LOGGING ==========

    return bv_size;
}

IGameObject* GameObjectsPool::at(int index) {
    return getActualVector().at(index);    
}

IGameObject* GameObjectsPool::operator[](int index) {
    return getActualVector().at(index);
}

void GameObjectsPool::operator+=(IGameObject* object) {
    push(object);
}

bool GameObjectsPool::isCanPushDirect() { return canPushDirect; }
bool GameObjectsPool::isNeedToFlush() { return needToFlush; }
bool GameObjectsPool::isNeedToOptimize() { return needToOptimize; }

std::vector<IGameObject*>& GameObjectsPool::getActualVector() { return actualVector; }
std::vector<IGameObject*>& GameObjectsPool::getBufferedVector() { return bufferedVector; }

int GameObjectsPool::getSize() { return actualVector.size(); }
int GameObjectsPool::getBufferSize() { return bufferedVector.size(); }
int GameObjectsPool::getTotalSize() { return getSize() + getBufferSize(); }