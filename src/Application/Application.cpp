#include "Application/Application.h"
#include <cstring>
#include <fstream>
#include <iterator>
#include <iostream>
#include "Utils/AF_JsonParser.h"



// Constructor that initializes the application and starts its lifecycle
Application::Application(const AppData& appDataInput, const std::shared_ptr<AppSubSystems> subSystemsInput) : appData(appDataInput), appSubSystem(subSystemsInput) {

    // Initialize the application and subsystems
    if(appSubSystem == nullptr){
        LogManager::Log("Application: Failed to create AppSubSystems");
        return;
    }

    int applicationStartupSuccess = startup(appSubSystem); // Initialize the application and subsystems
    if(applicationStartupSuccess < 1){
        LogManager::Log("Application: Startup failed");
        return;
    }

    loop(appSubSystem);    // Run the main application loop

    shutdown(appSubSystem);// Perform cleanup before exiting the application
}

// Destructor
Application::~Application() {}

// Startup function that initializes the application and subsystems
int Application::startup(const std::shared_ptr<AppSubSystems> subsystems) {
    int success = 1;
    LogManager::Log("Application: Startup");
    // Calculate the required buffer size for the formatted string
    constexpr int bufferSize = 256;
    char appDataPrintout[bufferSize];

    // Use snprintf to format the string and check for truncation
    int result = snprintf(appDataPrintout, bufferSize,
        "AppData:\n"
        "  applicationName: %s\n"
        "  windowXPos: %d\n"
        "  windowYPos: %d\n"
        "  windowWidth: %d\n"
        "  windowHeight: %d\n"
        "  mousefocus: %s\n"
        "  keyboardfocus: %s\n"
        "  fullscreen: %s\n"
        "  minimized: %s\n"
        "  isRunning: %s\n",
        appData.applicationName,
        appData.windowXPos,
        appData.windowYPos,
        appData.windowWidth,
        appData.windowHeight,
        appData.mouseFocus ? "true" : "false",
        appData.keyboardFocus ? "true" : "false",
        appData.fullscreen ? "true" : "false",
        appData.minimized ? "true" : "false",
        appData.isRunning ? "true" : "false"
        );

    //ensure we don't have an encoding error or truncation
    if (result >= bufferSize || result < 0) {
        
        std::cerr << "Buffer size is not large enough to accommodate the formatted string or an encoding error occurred." << std::endl;
        success = -1;
        return success;
    } else {
        LogManager::Log(appDataPrintout);
    }
    
    // Get a reference to the LogManager singleton instance
    appSubSystem->logManagerPtr = &LogManager::GetInstance();
    appSubSystem->gameEnginePtr = GameEngine::GetInstance();


    // Start up the LogManager
    int logManagerStartupSuccess = appSubSystem->logManagerPtr->startup();
    if(logManagerStartupSuccess < 1){
        LogManager::Log("LogManager: Startup failed");
        success = -1;
        return success;
    }


    int gameEngineStartupSuccess = appSubSystem->gameEnginePtr->startup(&appData, subsystems->engineBehaviourPtr, dependencyAppSubsystems);
    if(gameEngineStartupSuccess < 1){
        LogManager::Log("GameEngine: Startup failed");
        success = -1;
        return success;
    }else{
        LogManager::Log("GameEngine: Startup success");
    }
    appData.isRunning = true;
    
    return success;
}

// Main application loop
int Application::loop(const std::shared_ptr<AppSubSystems> subsystems) {
    // TODO: Implement the main loop code
    
    LogManager::Log("Application: Loop starting");
    while(appData.isRunning){
        subsystems->gameEnginePtr->loop(subsystems->engineBehaviourPtr, dependencyAppSubsystems);
    }
    return 0;
}

// Shutdown function that cleans up the application and subsystems
int Application::shutdown(const std::shared_ptr<AppSubSystems> subsystems) {
    // TODO: Implement the shutdown code
    LogManager::Log("Application: Shutdown");
    appData.isRunning = false;
    // Shutdown the LogManager
    subsystems->logManagerPtr->shutdown();
    subsystems->gameEnginePtr->shutdown(subsystems->engineBehaviourPtr);
    return 0;
}

// Function to initialize the application data with desired settings
AppData Application::InitializeAppData(const char* configPathName) {
    AppData appData;
    std::strcpy(appData.applicationName, "DEFAULT");
    appData.windowXPos = 0;
    appData.windowYPos = 0;
    appData.windowWidth = 720;
    appData.windowHeight = 640;
    appData.mouseFocus = true;
    appData.keyboardFocus = true;
    appData.fullscreen = false;
    appData.minimized = false;
    appData.isRunning = false;

    // Set the default applicationName
    std::strncpy(appData.applicationName, "DEFAULT", MAX_APP_NAME_LENGTH - 1);
    appData.applicationName[MAX_APP_NAME_LENGTH - 1] = '\0'; // Ensure null-termination

    // Attempt to open the JSON configuration file
    std::ifstream configFile(configPathName);

    //check if the config file is open
    if (configFile.good()) {
        try {
            // If the file is open, read the content and remove any whitespaces
            std::string content((std::istreambuf_iterator<char>(configFile)), std::istreambuf_iterator<char>());
            content = removeWhitespaces(content);

            // Remove the starting and ending curly braces
            content = content.substr(1, content.length() - 2);

            // Parse the key-value pairs and overwrite the default values
            std::map<std::string, std::string> configData = parseKeyValuePairs(content);

            // Get the application name
            std::string appName = configData["\"applicationName\""].substr(1, configData["\"applicationName\""].length() - 2);
            std::strncpy(appData.applicationName, appName.c_str(), MAX_APP_NAME_LENGTH - 1);
            appData.applicationName[MAX_APP_NAME_LENGTH - 1] = '\0'; // Ensure null-termination
            
            // Get the window position and size
            appData.windowXPos = std::stoi(configData["\"windowXPos\""]);
            appData.windowYPos = std::stoi(configData["\"windowYPos\""]);
            appData.windowWidth = std::stoi(configData["\"windowWidth\""]);
            appData.windowHeight = std::stoi(configData["\"windowHeight\""]);
            appData.fullscreen = configData["\"fullscreen\""] == "true";



        } catch (const std::exception& e) {
            std::cerr << "Error while parsing JSON configuration file: " << e.what() << std::endl;
            std::cerr << "Using default application settings" << std::endl;
        }
    }

    return appData;
}
