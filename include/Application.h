#pragma once
#include <cstring>
#include "LogManager.h"
#include "AF_JsonParser.h"
const int MAX_APP_NAME_LENGTH = 128;

// Structure to hold the application data, such as window properties and settings
struct AppData {
    char applicationName[MAX_APP_NAME_LENGTH];
    int windowXPos;
    int windowYPos;
    int windowWidth;
    int windowHeight;
    bool fullscreen;
};

// Structure to hold pointers to the various subsystems used by the Application
struct AppSubSystems {
    // Pointer to LogManager subsystem
    LogManager* logManagerPtr;

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
    // Startup function for initializing subsystems and resources
    int Startup();
    // Main application loop
    int Loop();
    // Shutdown function for cleaning up subsystems and resources
    int Shutdown();
};


