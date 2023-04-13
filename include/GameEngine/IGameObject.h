#pragma once

class IGameObject {
public:
    //virtual ~IGameObject() = 0;
    virtual void awake() {}
    virtual void start() {}
    virtual void update() {}
    virtual void shutdown() {}
};
