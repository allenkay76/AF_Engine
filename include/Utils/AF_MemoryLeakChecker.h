#pragma once

#include <iostream>
#ifdef _WIN64
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

class AF_MemoryLeakChecker {
public:
    // A static method to check for memory leaks.
    static void AF_CheckForMemoryLeaks() {
        #ifdef _WIN64
        // If we are on Windows, set the debug flags and check for memory leaks.
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

        if (_CrtDumpMemoryLeaks()) {
            std::cerr << "Memory Leak Detected" << std::endl;
        } else {
            std::cout << "No Memory Leaks Detected" << std::endl;
        }
        #endif 

        #ifdef __linux__
            // If we are on Linux, TODO: implement memory leak checker.
            std::cout << "TODO: implement linux memory checker" << std::endl;
        #endif

        #ifdef OSX
            // If we are on OSX, TODO: implement memory leak checker.
            std::cout << "TODO: implement OSX memory checker" << std::endl;
        #endif
    }
};

