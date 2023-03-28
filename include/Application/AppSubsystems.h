#pragma once
#include "Utils/LogManager.h"
#include "GameEngine/GameEngine.h"
#include "GameEngine/AF_EngineBehaviour.h"

// Structure to hold pointers to the various subsystems used by the Application
struct AppSubSystems {
    // Pointer to LogManager subsystem
    LogManager* logManagerPtr;
    std::shared_ptr<GameEngine> gameEnginePtr;

    std::shared_ptr<AF_EngineBehaviour> engineBehaviourPtr;

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