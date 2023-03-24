#pragma once
#include <stdio.h>
#include <vector>

#include "Utils/SingletonRoot.h"

#include "GameEngine/IScript.h"

// LogManager is a singleton class responsible for logging messages
class ScriptManager : public SingletonRoot {
public:
    // Get the singleton instance of LogManager
    static ScriptManager& GetInstance();

    // Initialize the LogManager
    int startup();

    // Shutdown the LogManager
    int shutdown();

    void addScript(IScript* script);

    void Awake();

    void Start();

    void Update();

    void LoadScripts(std::string scriptPath);

private:
    //script library
    void* scriptLibrary;
    
    // vector list of scripts
    std::vector<IScript*> scripts;

protected:
    // Declare member variables
    
    
    // Constructor for LogManager (singleton, should not be explicitly called)
    ScriptManager();

    // Destructor for LogManager (performs any necessary cleanup)
    ~ScriptManager();
};
