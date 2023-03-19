#include "GameEngine/GameEngine.h"
#include "Utils/LogManager.h"
#include "SDL/SDLGameRenderer.h"
#include "SDL/SDLGameInput.h"

//Singleton pattern to get the instance
GameEngine &GameEngine::GetInstance()
{
    static GameEngine instance;
    return instance;
}

//set the renderer
void GameEngine::setRenderer(IRenderer *renderer)
{
    LogManager::Log("GameEngine: Setting renderer");
    engineRenderer = renderer;
}

//Get the renderer
IRenderer *GameEngine::getRenderer()
{
    return engineRenderer;
}

//Startup
int GameEngine::startup(AppData* applicationData)
{
    LogManager::Log("GameEngine: Starting up");
    appData = applicationData;

    //This should be wrapped in if def for SDL
    engineRenderer = new SDLGameRenderer(); //not a singleton pattern
    engineInput = new SDLGameInput(); //not a singleton pattern

    
    //Initialize the renderer
    engineRenderer->Initialize(appData->applicationName, appData->windowWidth, appData->windowHeight);

    //Initialize the input
    engineInput->Initialize();
    return 0;
}

int GameEngine::loop()
{
    //Do a frame for the input and renderer
    engineInput->BeginFrame();
    engineInput->EndFrame();

    //Application will trigger a shutdown once it sees the isRunning flag is false
    if(engineInput->GetIsRunning() == false){
        appData->isRunning = false;
    }

    //Rendering
    engineRenderer->BeginFrame();
    engineRenderer->EndFrame();
    
    /**/
    return 0;
}

//Shutdown
int GameEngine::shutdown()
{
    LogManager::Log("GameEngine: Shutting down");
    
    engineInput->Shutdown();
    engineRenderer->Shutdown();

    //delete(engineRenderer);
    return 0;
}

//Constructor and destructor
GameEngine::GameEngine()
{
}

GameEngine::~GameEngine()
{
}