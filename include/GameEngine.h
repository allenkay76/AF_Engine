#pragma once
#include "IRenderer.h"
#include "SingletonRoot.h"
#include "AppData.h"

class GameEngine : SingletonRoot {
public:
    
    // Get the singleton instance of GameEngine
    static GameEngine& GetInstance();
    
    void setRenderer(IRenderer* renderer);
    IRenderer* getRenderer();

    // Initialize the GameEngine
    int startup(AppData* applicationData);

    // Run the main game loop
    int loop();
    // Shutdown the GameEngine
    int shutdown();

protected:
    IRenderer* engineRenderer;
    AppData* appData;
    // Constructor for GameEngine (singleton, should not be explicitly called)
    GameEngine();

    // Destructor for GameEngine (performs any necessary cleanup)
    ~GameEngine();
};
