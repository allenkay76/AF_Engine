#pragma once
#include "AppData.h"
#include "LogManager.h"
#include "GameEngine.h"






// Structure to hold pointers to the various subsystems used by the Application
struct AppSubSystems {
    // Pointer to LogManager subsystem
    LogManager* logManagerPtr;
    GameEngine* gameEnginePtr;
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


class Application {
public:
    // Application subsystems and data
    AppSubSystems appSubSystem;
    AppData appData;

    // Constructor that takes a reference to an AppData object
    Application(const AppData& appDataInput);
    // Destructor
    ~Application();

    static AppData InitializeAppData(const char* configPathName);

    

private:
    //SDL Stuff
    

    // Startup function for initializing subsystems and resources
    int startup();
    // Main application loop
    int loop();
    // Shutdown function for cleaning up subsystems and resources
    int shutdown();
};


