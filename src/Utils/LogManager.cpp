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
void LogManager::Log(const char* message, ...) {
    va_list args;
    va_start(args, message);

    char buffer[1024];
    int result = vsnprintf(buffer, sizeof(buffer), message, args);

    va_end(args);

    if (result < 0) {
        std::cerr << "Error in Log: vsnprintf returned a negative value" << std::endl;
        return;
    }

    std::string outputBuffer(buffer, result);
    std::size_t len = outputBuffer.length();

    for (char& c : outputBuffer) {
        if (c == '\0') {
            // replace null characters with a space to avoid truncated output
            c = ' ';
        }
    }

    static bool previousCR = true; // initialize previousCR to true
    if (previousCR) {
        std::cout << outputBuffer << std::endl; // print a new line
    } else {
        std::cout << '\r' << std::string(len, ' ') << '\r' << outputBuffer << std::flush; // overwrite current line
    }

    // update previousCR
    previousCR = (outputBuffer[len - 1] == '\r');
}

// Initialize the LogManager
int LogManager::startup() {
    
    return 1;
}

// Shutdown the LogManager
int LogManager::shutdown() {
    
    return 1;
}

// Constructor for LogManager (singleton, should not be explicitly called)
LogManager::LogManager() {}

// Destructor for LogManager (performs any necessary cleanup)
LogManager::~LogManager() {
    // Implement any cleanup code, if necessary
}
