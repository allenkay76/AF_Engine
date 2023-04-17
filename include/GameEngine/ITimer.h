#pragma once
#define AF_ENGINE_EXPORTS
#ifdef AF_ENGINE_EXPORTS
#define AF_Engine_API __declspec(dllexport)
#else
#define AF_Engine_API __declspec(dllimport)
#endif

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

    virtual void countFrameTick() = 0;
    virtual unsigned int getFrameTicks() = 0;
    virtual unsigned int getCountedFrames() = 0;
    virtual float getAvgFrameRate() = 0;

    virtual bool isStarted() = 0;
    virtual bool isPaused() = 0;

    //virtual ~ITimer() = default;

};

//Null service pattern, initialised in the constructor of inputLocator
class NullITimer: public ITimer {
public:
    virtual bool Initialize() {return false;}
    virtual void Shutdown() {}
    virtual void start() {}
    virtual void stop() {}
    virtual void pause() {}
    virtual void unpause() {}

    virtual void countFrameTick() {}
    virtual unsigned int getFrameTicks() {return 0;}
    unsigned int getCountedFrames() {return 0;}
    virtual float getAvgFrameRate() {return 0;}

    virtual bool isStarted() {return false;}
    virtual bool isPaused() {return false;}
private:
    unsigned int m_startTicks = 0;          
    unsigned int m_pausedTicks = 0;         
    unsigned int m_countedFrames = 0;
    unsigned int m_frameTicks = 0;
    float m_frameRate = 0;
    bool m_paused = false;                     
    bool m_started = false;    

};

//Service Locator Pattern
//https://gameprogrammingpatterns.com/service-locator.html
class ITimerLocator {
private: 
    static ITimer* m_service;
    static NullITimer m_nullService;
    
public:
    static void initialize(); 

    AF_Engine_API static ITimer* getTimer(); 

    static void provide(ITimer* service){
        if(service == nullptr){
            //revert to null service
            m_service = &m_nullService;
        }else{
            m_service = service;
        }
        m_service = service;
    }

};
