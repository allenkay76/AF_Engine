#pragma once // Header guard to ensure this file is included only once in a compilation unit
#define AF_ENGINE_EXPORTS
#ifdef AF_ENGINE_EXPORTS
#define AF_Engine_API __declspec(dllexport)
#else
#define AF_Engine_API __declspec(dllimport)
#endif
// Include necessary header files
#include <memory>
#include "GameEngine/IRenderer.h"
#include "GameEngine/IInput.h"
#include "Utils/SingletonRoot.h"
#include "Application/AppData.h"
#include "GameEngine/AF_EngineBehaviour.h"
//#include "Rendering/IRenderData.h"
#include "GameEngine/IWindow.h"
#include "GameEngine/IEventHandler.h"
#include "GameEngine/IFontRenderer.h"
#include "GameEngine/ITimer.h"

#include "Application/DependencyAppSubsystems.h"


class Game;
struct DependencyAppSubSystem;

class GameEngine : SingletonRoot { // Define the GameEngine class and inherit from SingletonRoot

public:
    // Get the singleton instance of GameEngine
    //static GameEngine& GetInstance();
    AF_Engine_API static std::shared_ptr<GameEngine> GetInstance();
    // Set and get the renderer
    void setRenderer( IRenderer* renderer);
    //AF_Engine_API IRenderer* getRenderer();
    IRenderer* getRenderer();

    // Initialize the GameEngine
    int startup(AppData* applicationData, const std::shared_ptr<AF_EngineBehaviour> engineBehaviour,  DependencyAppSubsystems& dependencyAppSubSystems);

    // Run the main game loop
    int loop(const std::shared_ptr<AF_EngineBehaviour> engineBehaviour, DependencyAppSubsystems& dependencyAppSubSystems);

    // Shutdown the GameEngine
    int shutdown(const std::shared_ptr<AF_EngineBehaviour> engineBehaviour,DependencyAppSubsystems& dependencyAppSubSystems);

    //Called by main() to load the game DLL:
    void LoadGameDLL();

    AppData* getAppData();

    // Declare the constructor for GameEngine (singleton, should not be explicitly called)
    GameEngine();

    // Declare the destructor for GameEngine (performs any necessary cleanup)
    ~GameEngine();
private:
    Game* game;
    AppData* appData;
};
