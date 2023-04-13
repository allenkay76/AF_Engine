#pragma once
#define AF_ENGINE_EXPORTS
#ifdef AF_ENGINE_EXPORTS
#define AF_Engine_API __declspec(dllexport)
#else
#define AF_Engine_API __declspec(dllimport)
#endif
/*
This code defines an interface class IInput, 
which is intended to provide an abstracted interface for handling input for a game engine. 
The class defines several pure virtual functions that must be implemented by any derived classes that inherit from IInput, 
including functions for initialization, shutdown, beginning and ending a frame, and getting whether the application is running.
*/
class IInput {
public:
    virtual bool Initialize() = 0;
    virtual void Shutdown() = 0;
    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;
    virtual bool GetIsRunning() = 0;

    virtual bool getKeyPressed() = 0;
};



//Null service pattern, initialised in the constructor of inputLocator
class NullIInput: public IInput {
public:
    virtual bool Initialize() {return false;}
    virtual void Shutdown() {}
    virtual void BeginFrame() {}
    virtual void EndFrame() {}
    virtual bool GetIsRunning() {return false;}

    virtual bool getKeyPressed() {return false;};
};

//Service Locator Pattern
//https://gameprogrammingpatterns.com/service-locator.html
class IInputLocator {
private: 
    static IInput* m_service;
    static NullIInput m_nullService;
    
public:
    static void initialize(); 

    AF_Engine_API static IInput* getInput(); 

    static void provide(IInput* service){
        if(service == nullptr){
            //revert to null service
            m_service = &m_nullService;
        }else{
            m_service = service;
        }
        m_service = service;
    }

};

