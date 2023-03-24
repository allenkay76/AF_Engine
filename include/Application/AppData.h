#pragma once

// Structure to hold the application data, such as window properties and settings
const int MAX_APP_NAME_LENGTH = 128;
const int MAX_SCRIPT_NAME_LENGTH = 128;

// Structure to hold the application data, such as window properties and settings
struct AppData {
    char applicationName[MAX_APP_NAME_LENGTH];
    int windowXPos;
    int windowYPos;
    int windowWidth;
    int windowHeight;
    bool fullscreen;
    bool isRunning;
    char scriptPath[MAX_SCRIPT_NAME_LENGTH];
};