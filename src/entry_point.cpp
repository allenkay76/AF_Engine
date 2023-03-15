#include <cstdio>
#include <cstring>
#include "AF_JsonParser.h"
#include "Application.h"

// Function to initialize the application data with desired settings
AppData initializeAppData() {
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
    std::ifstream configFile("config/AF_Engine.json");

    if (configFile.is_open()) {
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
    }

    return appData;
}

int main(int argc, char* args[]) {
    // Print the starting message and display the command-line arguments
    printf("Starting AF_Engine entry point\n");
    printf("Number of arguments: %d\n", argc);
    printf("First argument: %s\n", args[0]);


    // Initialize the application data structure with the desired settings
    AppData appData = initializeAppData();

    // Create an Application instance with the specified application data
    Application application(appData);

    // The program exits successfully
    return 0;
}
