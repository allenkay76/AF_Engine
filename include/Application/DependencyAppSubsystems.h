#pragma once

//If we are using the SDL systems then create a struct containing the relevant subsystems
#ifdef SDL_GAME_RENDERER
#include "SDL/SDLGameTimer.h"

struct DependencyAppSubsystems{
    // Pointer to LogManager subsystem
    SDLGameTimer gameTimer;
    // Uncomment and add the relevant headers to use the following subsystems
    // MemoryManager* memoryManagerPtr;
    // TimeManager* timeManagerPtr;
    // ApplicationStruct* applicationStructPtr;
    // InputManager* inputManagerPtr;
    // SceneManager* sceneManagerPtr;
    // UIManager* uiManagerPtr;
    // PhysicsManager* physicsManager;
    // RendererManager* rendererManager;
    // ExceptionManager* exceptionManager;
    // SoundManager* soundManager;
};

#else
struct DependencyAppSubsystems{
};
#error "SDL_GAME_RENDERER flag is not defined"
#endif