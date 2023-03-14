#include "Application.h"

Application::Application() {
    Startup();
    Loop();
    Shutdown();
}

Application::~Application() {}

int Application::Startup() {
    // TODO: Implement startup code
    LogManager::Log("Application: Startup");
    appSubSystem.logManagerPtr = &LogManager::GetInstance();
    appSubSystem.logManagerPtr->Startup();
    return 0;
}

int Application::Loop() {
    // TODO: Implement main loop code
    LogManager::Log("Application: Loop");
    return 0;
}

int Application::Shutdown() {
    // TODO: Implement shutdown code
    LogManager::Log("Application: Shutdown");
    appSubSystem.logManagerPtr->Shutdown();

    if(appSubSystem.logManagerPtr != nullptr){
        appSubSystem.logManagerPtr->DestroyInstance();
        appSubSystem.logManagerPtr = nullptr;
    }

    return 0;
}