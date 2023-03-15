#include <cstdio>
#include "Application.h"

// Function to initialize the application data with desired settings
AppData initializeAppData(const char* engineName) {
    AppData appData = {
        engineName, // applicationName
        0,          // windowXPos
        0,          // windowYPos
        720,        // windowWidth
        640,        // windowHeight
        false       // fullscreen
    };
    return appData;
}

int main(int argc, char* args[]) {
    // Print the starting message and display the command-line arguments
    printf("Starting AF_Engine entry point\n");
    printf("Number of arguments: %d\n", argc);
    printf("First argument: %s\n", args[0]);

    // Define the name of the engine
    const char* engineName = "AF_Engine";

    // Initialize the application data structure with the desired settings
    AppData appData = initializeAppData(engineName);

    // Create an Application instance with the specified application data
    Application application(appData);

    // The program exits successfully
    return 0;
}
