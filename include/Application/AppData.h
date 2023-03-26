#pragma once
#include "GameEngine/AF_EngineBehaviour.h"
#include <cstring>
#include <algorithm>
#include <memory>

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
    bool fullscreen;
    bool isRunning;
    AF_EngineBehaviour* afEngineBehaviourPtr;
    
    // Default constructor
    AppData() :
        windowXPos(0),
        windowYPos(0),
        windowWidth(720),
        windowHeight(640),
        fullscreen(false),
        isRunning(false),
        afEngineBehaviourPtr(nullptr)
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
        fullscreen = other.fullscreen;
        isRunning = other.isRunning;
        afEngineBehaviourPtr = other.afEngineBehaviourPtr;
    }
};