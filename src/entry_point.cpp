#include <cstdio>
#include "Application.h"



int main(int argc, char* args[]) {
    // Print the starting message and display the command-line arguments
    printf("Starting AF_Engine entry point\n");
    printf("Number of arguments: %d\n", argc);

    //Check if there is a config file path argument
    if(argc > 1){
        printf("First argument: %s\n", args[1]);
        // Initialize the application data structure with the desired settings, use the first argument as the config file path
        AppData appData = Application::InitializeAppData(args[1]);
        // Create an Application instance with the specified application data
        Application application(appData);
    }else{
        printf("Missing Project Config File Path\n");
    }
    
    // The program exits successfully
    return 0;
}
