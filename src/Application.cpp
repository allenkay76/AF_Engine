#include "Application.h"

// Constructor that initializes the application and starts its lifecycle
Application::Application(const AppData& appDataInput) : appData(appDataInput) {
    Startup(); // Initialize the application and subsystems

    Loop();    // Run the main application loop

    Shutdown();// Perform cleanup before exiting the application
}

// Destructor
Application::~Application() {}

// Startup function that initializes the application and subsystems
int Application::Startup() {
    LogManager::Log("Application: Startup");
    // Create a buffer to store the formatted string
    char appDataPrintout[256];

    // Use snprintf to format the string
    snprintf(appDataPrintout, sizeof(appDataPrintout),
        "AppData:\n"
        "  applicationName: %s\n"
        "  windowXPos: %d\n"
        "  windowYPos: %d\n"
        "  windowWidth: %d\n"
        "  windowHeight: %d\n"
        "  fullscreen: %s\n",
        appData.applicationName,
        appData.windowXPos,
        appData.windowYPos,
        appData.windowWidth,
        appData.windowHeight,
        appData.fullscreen ? "true" : "false");
    LogManager::Log(appDataPrintout);

    // Get a reference to the LogManager singleton instance
    appSubSystem.logManagerPtr = &LogManager::GetInstance();

    // Start up the LogManager
    appSubSystem.logManagerPtr->Startup();

    return 0;
}

// Main application loop
int Application::Loop() {
    // TODO: Implement the main loop code
    LogManager::Log("Application: Loop");
    return 0;
}

// Shutdown function that cleans up the application and subsystems
int Application::Shutdown() {
    // TODO: Implement the shutdown code
    LogManager::Log("Application: Shutdown");

    // Shutdown the LogManager
    appSubSystem.logManagerPtr->Shutdown();

    return 0;
}
