#include "Utils/LogManager.h"
#include <stdarg.h> // for va_list, va_start, and va_end
#include <iostream>
#include <memory>
#include <dlfcn.h>
#include <cstring> // for memcpy
#include "GameEngine/ScriptManager.h"
#include "GameEngine/IScript.h"
#include "GameEngine/ScriptManager.h"
#include "GameEngine/ScriptManager.h"

/*
This creates a type alias for a function pointer that takes no arguments and returns a pointer to an IScript object. 
You can then use create_function_t in the rest of the code to declare function pointers with this signature
*/
using create_function_t = IScript* (*)();


// Get the singleton instance of LogManager
ScriptManager& ScriptManager::GetInstance() {
    static ScriptManager instance;
    return instance;
}

// Initialize the ScriptManager
int ScriptManager::startup() {
    LogManager::Log("ScriptManager: Starting up");

    Awake();
    Start();
    return 1;
}

// Shutdown the ScriptManager
int ScriptManager::shutdown() {
    LogManager::Log("ScriptManager: Shutting down");
    // Unload the script library
    dlclose(scriptLibrary);
    return 1;
}

void ScriptManager::addScript(IScript *script)
{
    if(script != nullptr){
        LogManager::Log("ScriptManager: Adding script");
        scripts.push_back(script);
    }else{
        LogManager::Log("ScriptManager: Script is null");
    }
    
}
void ScriptManager::Awake()
{
    for (unsigned int i = 0; i < scripts.size(); i++)
    {
        scripts[i]->Awake();
    }
}

void ScriptManager::Start()
{
    for(unsigned int i = 0; i < scripts.size(); i++)
    {
        scripts[i]->Start();
    }
}

void ScriptManager::Update()
{
    for(unsigned int i = 0; i < scripts.size(); i++)
    {
        scripts[i]->Update();
    }
}
void ScriptManager::LoadScripts(std::string scriptPath)
{
    /*
    No, that code will not work as it's trying to load a .cpp file directly as a library, whereas a compiled library file (e.g., .so file) is required for dynamic linking.

To load a compiled library file for the script (e.g., .so file) located in the scripts folder, you could use:
    */

    LogManager::Log("ScriptManager: Loading script %s", scriptPath.c_str());
    // Load the script library using dynamic linking
    // ///std::string(scriptPath).substr(0, std::string(scriptPath).find_last_of('.')) + ".cpp";
    std::string scriptLibraryFilename = "scripts/draw_image.cpp";

    scriptLibrary = dlopen(scriptLibraryFilename.c_str(), RTLD_NOW);
    if (!scriptLibrary) {
        LogManager::Log("ScriptManager: Failed to load script library");
        std::cerr << "Failed to load script library: " << dlerror() << std::endl;
        return;
    }

    // Get a pointer to the script's factory function
    std::string className = scriptPath.substr(scriptPath.find_last_of('/') + 1);
    className = className.substr(0, className.find_last_of('.'));
    std::string factoryFunctionName = "Create_" + className;
    create_function_t createFunction = reinterpret_cast<create_function_t>(dlsym(scriptLibrary, factoryFunctionName.c_str()));
    if (!createFunction) {
        LogManager::Log("ScriptManager: Failed to load factory function for script");
        std::cerr << "Failed to load factory function for script: " << dlerror() << std::endl;
        return;
    }

    // Call the factory function to create an instance of the script
    std::unique_ptr<IScript> script(createFunction());


    // Add the script to the script manager
    addScript(script.get());
}

// Constructor for ScriptManager (singleton, should not be explicitly called)
ScriptManager::ScriptManager() {}

// Destructor for ScriptManager (performs any necessary cleanup)
ScriptManager::~ScriptManager() {
    // Implement any cleanup code, if necessary
}

