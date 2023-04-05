#pragma once
#include <SDL2/SDL.h>
#include "GameEngine/ITimer.h"


class SDLGameTimer: public ITimer {   // define the SDLGameInput class and inherit from IInput
public:

    bool Initialize() override;       // declare the Initialize function, which is a pure virtual function in IInput
    void Shutdown() override;         // declare the Shutdown function, which is a pure virtual function in IInput
    void start() override;
    void stop() override;
    void pause() override;
    void unpause() override;

    int getTicks() override;

    bool isStarted() override;
    bool isPaused() override;

    
    // implement other rendering functions using SDL2 API
    SDLGameTimer();                   // declare the constructor for the SDLGameInput class
    ~SDLGameTimer();                  // declare the destructor for the SDLGameInput class
};