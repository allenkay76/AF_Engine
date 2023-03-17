#include "Application.h"
#include <cstring>
#include <fstream>
#include <iterator>
#include <iostream>
#include "AF_JsonParser.h"

// Constructor that initializes the application and starts its lifecycle
Application::Application(const AppData& appDataInput) : appData(appDataInput) {
    startup(); // Initialize the application and subsystems

    loop();    // Run the main application loop

    shutdown();// Perform cleanup before exiting the application
}

// Destructor
Application::~Application() {}

// Startup function that initializes the application and subsystems
int Application::startup() {
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
        "  fullscreen: %s\n",
        appData.applicationName,
        appData.windowXPos,
        appData.windowYPos,
        appData.windowWidth,
        appData.windowHeight,
        appData.fullscreen ? "true" : "false");

    //ensure we don't have an encoding error or truncation
    if (result >= bufferSize || result < 0) {
        std::cerr << "Buffer size is not large enough to accommodate the formatted string or an encoding error occurred." << std::endl;
    } else {
        LogManager::Log(appDataPrintout);
    }
    
    // Get a reference to the LogManager singleton instance
    appSubSystem.logManagerPtr = &LogManager::GetInstance();

    // Start up the LogManager
    appSubSystem.logManagerPtr->startup();

    return 0;
}

// Main application loop
int Application::loop() {
    // TODO: Implement the main loop code
    LogManager::Log("Application: Loop");
    return 0;
}

// Shutdown function that cleans up the application and subsystems
int Application::shutdown() {
    // TODO: Implement the shutdown code
    LogManager::Log("Application: Shutdown");

    // Shutdown the LogManager
    appSubSystem.logManagerPtr->shutdown();

    return 0;
}

// Function to initialize the application data with desired settings
AppData Application::InitializeAppData(const char* configPathName) {
    AppData appData = {
        "DEFAULT", // applicationName
        0,          // windowXPos
        0,          // windowYPos
        720,        // windowWidth
        640,        // windowHeight
        false       // fullscreen
    };

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
            std::string appName = configData["\"applicationName\""].substr(1, configData["\"applicationName\""].length() - 2);
            std::strncpy(appData.applicationName, appName.c_str(), MAX_APP_NAME_LENGTH - 1);
            appData.applicationName[MAX_APP_NAME_LENGTH - 1] = '\0'; // Ensure null-termination
            
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
