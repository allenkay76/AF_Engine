#include "LogManager.h"


LogManager& LogManager::GetInstance() {
    static LogManager instance;
    return instance;
}

void LogManager::Log(const char* message) {
    // log the message
    printf("%s\n", message);
}

int LogManager::Startup(){
    Log("LogManager: Starting up");
    return 1;
}

int LogManager::Shutdown(){
    Log("LogManager: Shutting up");
    return 1;
}

void LogManager::DestroyInstance(){
    delete &GetInstance();
}


LogManager::LogManager() {
    // Constructor that should never happen
}

LogManager::~LogManager() {
    // cleanup the logger
}