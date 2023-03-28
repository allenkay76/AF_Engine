#pragma once
#define AF_ENGINE_EXPORTS
#ifdef AF_ENGINE_EXPORTS
#define AF_Engine_API __declspec(dllexport)
#else
#define AF_Engine_API __declspec(dllimport)
#endif

#include <memory>
#include "Application/AppData.h"
#include "Utils/LogManager.h"
#include "GameEngine/GameEngine.h"

#include "GameEngine/AF_EngineBehaviour.h"
#include "Application/AppSubsystems.h"


class AF_Engine_API Application {
public:
    // Application subsystems and data
    AppData appData;
    std::shared_ptr<AppSubSystems> appSubSystem;
    

    // Constructor that takes a reference to an AppData object
    Application(const AppData& appDataInput, const std::shared_ptr<AppSubSystems> subSystemsInput);
    // Destructor
    ~Application();

    static AppData InitializeAppData(const char* configPathName);

    //To be defined in client.
    Application CreateApplication();
    // Startup function for initializing subsystems and resources
    int startup(const std::shared_ptr<AppSubSystems> subsystems);
    // Main application loop
    int loop(const std::shared_ptr<AppSubSystems> subsystems);
    // Shutdown function for cleaning up subsystems and resources
    int shutdown(const std::shared_ptr<AppSubSystems> subsystems);

private:
    //SDL Stuff
    
};


