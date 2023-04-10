#pragma once

//If we are using the SDL systems then create a struct containing the relevant subsystems
#ifdef SDL_GAME_RENDERER
#include "SDL/SDLGameTimer.h"
#include "SDL/SDLEventHandler.h"
#include "SDL/SDLFontRenderer.h"
#include "SDL/SDLGameInput.h"
#include "SDL/SDLGameWindow.h"

struct DependencyAppSubsystems{
    // Pointer to LogManager subsystem
    SDLGameTimer gameTimer;
    SDLEventHandler eventHandler;
    SDLFontRenderer fontRenderer;
    SDLGameInput gameInput;
    SDLGameWindow gameWindow;
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