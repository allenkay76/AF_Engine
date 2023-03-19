#pragma once
#include "Utils/SingletonRoot.h"
#include <stdio.h>

// LogManager is a singleton class responsible for logging messages
class LogManager : public SingletonRoot {
public:
    // Get the singleton instance of LogManager
    static LogManager& GetInstance();

    // Log a message to the console
    static void Log(const char* message, ...);

    // Initialize the LogManager
    int startup();

    // Shutdown the LogManager
    int shutdown();

protected:
    // Constructor for LogManager (singleton, should not be explicitly called)
    LogManager();

    // Destructor for LogManager (performs any necessary cleanup)
    ~LogManager();
};
