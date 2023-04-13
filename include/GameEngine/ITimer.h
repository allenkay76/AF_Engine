#pragma once
#include <memory>


class ITimer {
public:
    virtual bool Initialize() = 0;
    virtual void Shutdown() = 0;

    //The various clock actions
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void pause() = 0;
    virtual void unpause() = 0;

    virtual int getTicks() const = 0;

    virtual bool isStarted() = 0;
    virtual bool isPaused() = 0;

    virtual ~ITimer() = default;


    

};