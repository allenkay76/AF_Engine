#pragma once // Header guard to ensure this file is included only once in a compilation unit

// Include necessary header files
#include "GameEngine/ScriptManager.h"
#include "GameEngine/IRenderer.h"
#include "GameEngine/IInput.h"
#include "Utils/SingletonRoot.h"
#include "Application/AppData.h"
#include "SDL/SDLRenderData.h"

class GameEngine : SingletonRoot { // Define the GameEngine class and inherit from SingletonRoot
public:
    // Get the singleton instance of GameEngine
    static GameEngine& GetInstance();
    
    // Set and get the renderer
    void setRenderer(IRenderer* renderer);
    IRenderer* getRenderer();

    // Initialize the GameEngine
    int startup(AppData* applicationData);

    // Run the main game loop
    int loop();

    // Shutdown the GameEngine
    int shutdown();

protected:
    // Declare member variables
    IRenderer* engineRenderer;
    IInput* engineInput;
    AppData* appData;
    SDLRenderData* sdlData;

    ScriptManager* scriptManager;

    // Declare the constructor for GameEngine (singleton, should not be explicitly called)
    GameEngine();

    // Declare the destructor for GameEngine (performs any necessary cleanup)
    ~GameEngine();
};
