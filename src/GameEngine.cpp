#include "GameEngine.h"
#include "LogManager.h"
#include "AppData.h"
#include "SDLGameRenderer.h"


GameEngine &GameEngine::GetInstance()
{
    static GameEngine instance;
    return instance;
}

void GameEngine::setRenderer(IRenderer *renderer)
{
    LogManager::Log("GameEngine: Setting renderer");
    engineRenderer = renderer;
}

IRenderer *GameEngine::getRenderer()
{
    return engineRenderer;
}

int GameEngine::startup(AppData* applicationData)
{
    LogManager::Log("GameEngine: Starting up");
    appData = applicationData;
    engineRenderer = new SDLGameRenderer();
    engineRenderer->Initialize(appData->applicationName, appData->windowWidth, appData->windowHeight);
    return 0;
}

int GameEngine::loop()
{
    
    if(engineRenderer->BeginFrame() == false){
        appData->isRunning = false;
    }else{
        engineRenderer->EndFrame();
    }
    /**/
    return 0;
}

int GameEngine::shutdown()
{
    LogManager::Log("GameEngine: Shutting down");
    //delete engineRenderer;
    engineRenderer->Shutdown();
    //delete(engineRenderer);
    return 0;
}

GameEngine::GameEngine()
{
}

GameEngine::~GameEngine()
{
}
