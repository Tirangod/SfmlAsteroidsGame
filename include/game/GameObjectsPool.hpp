#ifndef GameObjectsList_HPP
#define GameObjectsList_HPP

#include <vector>
#include <string>

#include <game/IGameObject.hpp>
#include <game/Logger.hpp>

class GameObjectsPool {
private:
    bool needToOptimize;
    bool needToFlush;
    bool canPushDirect;
    std::vector<IGameObject*> actualVector;
    std::vector<IGameObject*> bufferedVector;

public:
    GameObjectsPool();

    void block();
    void optimize();
    void checkOptimization();

    void directPush(IGameObject* object);
    void set(IGameObject *obj, int index);
    void push(IGameObject* object);
    int flush();
    IGameObject* at(int index);

    bool isCanPushDirect();
    bool isNeedToFlush();
    bool isNeedToOptimize();

    int getSize();
    int getBufferSize();
    int getTotalSize();

    IGameObject* operator[](int index);
    void operator+=(IGameObject* object);
    
    std::vector<IGameObject*>& getActualVector();
    std::vector<IGameObject*>& getBufferedVector();

};

#endif
