#pragma once
#include "SingletonRoot.h"
#include <stdio.h>

class LogManager : public SingletonRoot {
public:
    static LogManager& GetInstance();
    static void Log(const char* message);
    int Startup();
    int Shutdown();
    void DestroyInstance();

protected:
    LogManager();
    ~LogManager();
};
