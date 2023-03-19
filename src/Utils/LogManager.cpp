#include "Utils/LogManager.h"
#include <stdarg.h> // for va_list, va_start, and va_end
#include <iostream>
#include <cstring> // for memcpy

// Get the singleton instance of LogManager
LogManager& LogManager::GetInstance() {
    static LogManager instance;
    return instance;
}

// Log a message to the console
void LogManager::Log(const char* message,  ...) {
    const int size = 1024;
    char buffer[size];
    char* dynamicBuffer = nullptr;
    char* outputBuffer = buffer;

    va_list args; // initialize a variable argument list
    va_start(args, message); // start processing the variable argument list

    // use vsnprintf to format the arguments into a string
    int result = vsnprintf(buffer, size, message, args);

    va_end(args); // end processing the variable argument list

    if (result < 0) {
        // error occurred
        std::cerr << "Error in Log: vsnprintf returned a negative value" << std::endl;
        return;
    }

    if (result >= size) {
        // formatted string did not fit in buffer, so allocate a larger buffer
        dynamicBuffer = new char[result + 1];
        outputBuffer = dynamicBuffer;

        va_list args2;
        va_start(args2, message);
        result = vsnprintf(dynamicBuffer, result + 1, message, args2);
        va_end(args2);

        if (result < 0) {
            // error occurred
            std::cerr << "Error in Log: vsnprintf returned a negative value" << std::endl;
            delete[] dynamicBuffer;
            return;
        }
    }

    std::size_t len = std::strlen(outputBuffer);
    char* end = outputBuffer + len;
    for (char* p = outputBuffer; p != end; ++p) {
        if (*p == '\0') {
            // replace null characters with a space to avoid truncated output
            *p = ' ';
        }
    }

    std::cout.write(outputBuffer, len) << std::endl;

    if (dynamicBuffer != nullptr) {
        delete[] dynamicBuffer;
    }
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
