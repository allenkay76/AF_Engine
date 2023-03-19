#include "Utils/LogManager.h"
#include <iostream>

// Get the singleton instance of LogManager
LogManager& LogManager::GetInstance() {
    static LogManager instance;
    return instance;
}

// Log a message to the console
void LogManager::Log(const char* message) {
    std::cout << message << std::endl;
}

// Initialize the LogManager
int LogManager::startup() {
    Log("LogManager: Starting up");
    return 1;
}

// Shutdown the LogManager
int LogManager::shutdown() {
    Log("LogManager: Shutting down");
    return 1;
}

// Constructor for LogManager (singleton, should not be explicitly called)
LogManager::LogManager() {}

// Destructor for LogManager (performs any necessary cleanup)
LogManager::~LogManager() {
    // Implement any cleanup code, if necessary
}
