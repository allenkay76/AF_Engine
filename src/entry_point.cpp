
#include <iostream>
#include <stdlib.h>

#include "Application.h"
#include "AF_MemoryLeakChecker.h"





int main(int argc, char* args[]) {
    // Print the starting message and display the command-line arguments
    std::cout << "Starting AF_Engine entry point" << std::endl;
    std::cout << "Number of arguments: " << argc << std::endl;

    


    //Check if there is a config file path argument
    if(argc > 1){
        std::cout << "First argument: " << args[1] << std::endl;
        // Initialize the application data structure with the desired settings, use the first argument as the config file path
        AppData appData = Application::InitializeAppData(args[1]);
        // Create an Application instance with the specified application data
        Application application(appData);
    }else{
        std::cout << "Missing Project Config File Path"<< std::endl;
    }
    
    //MemoryLeakTest
    //int* x = (int*)malloc(sizeof(int)); // Allocate an integer on the heap testing a leak detection
    AF_MemoryLeakChecker::AF_CheckForMemoryLeaks();
    
    
    // The program exits successfully
    return 0;
}
