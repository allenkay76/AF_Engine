#pragma once
#include <memory>

/*
This code defines an interface class IInput, 
which is intended to provide an abstracted interface for handling input for a game engine. 
The class defines several pure virtual functions that must be implemented by any derived classes that inherit from IInput, 
including functions for initialization, shutdown, beginning and ending a frame, and getting whether the application is running.
*/
class IWindow {
public:
    virtual bool Initialize(const char* windowName, const int windowWidth, const int windowHeight) = 0;
    virtual void Shutdown() = 0;
    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;
    virtual bool GetIsRunning() = 0;

    
};
