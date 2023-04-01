#pragma once
#include <cstring>
#include <algorithm>
#include <memory>

// Forward declaration of AF_EngineBehaviour

// Structure to hold the application data, such as window properties and settings
const int MAX_APP_NAME_LENGTH = 128;

// Structure to hold the application data, such as window properties and settings
struct AppData {
    //AppData Structure
    char applicationName[MAX_APP_NAME_LENGTH];
    int windowXPos;
    int windowYPos;
    int windowWidth;
    int windowHeight;
    bool mouseFocus;
    bool keyboardFocus;
    bool fullscreen;
    bool minimized;
    bool isRunning;
    //AF_EngineBehaviour* afEngineBehaviourPtr;
    //std::shared_ptr<GameEngine> gameEnginePtr;
    
    // Default constructor
    AppData() :
        windowXPos(0),
        windowYPos(0),
        windowWidth(720),
        windowHeight(640),
        mouseFocus(false),
        keyboardFocus(false),
        fullscreen(false),
        minimized(false),
        isRunning(false)
    {
        std::strncpy(applicationName, "DEFAULT", MAX_APP_NAME_LENGTH - 1);
        applicationName[MAX_APP_NAME_LENGTH - 1] = '\0';
    }

    // Copy constructor
    AppData(const AppData& other) {
        std::strcpy(applicationName, other.applicationName);
        windowXPos = other.windowXPos;
        windowYPos = other.windowYPos;
        windowWidth = other.windowWidth;
        windowHeight = other.windowHeight;
        mouseFocus = other.mouseFocus;
        keyboardFocus = other.keyboardFocus;
        fullscreen = other.fullscreen;
        minimized = other.minimized;
        isRunning = other.isRunning;
    }
};