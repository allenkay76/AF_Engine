#include "GameEngine/GameEngine.h"
#include "Utils/LogManager.h"
//#include "SDL/SDLGameWindow.h"
#include "SDL/SDLGameRenderer.h"
//#include "SDL/SDLGameInput.h"
//#include "SDL/SDLEventHandler.h"
//#include "SDL/SDLFontRenderer.h"
#include "SDL/SDLGameTimer.h"
#include "GameEngine/AF_EngineBehaviour.h"

#include <iostream>


//Singleton pattern to get the instance
std::shared_ptr<GameEngine> GameEngine::GetInstance()
{
    static std::shared_ptr<GameEngine> instance = std::make_shared<GameEngine>();
    return instance;
}

IRenderer *GameEngine::getRenderer()
{
    return nullptr;
}

//Startup
int GameEngine::startup(AppData* applicationData, const std::shared_ptr<AF_EngineBehaviour> engineBehaviour, DependencyAppSubsystems& dependencyAppSubSystems) 
{
    int success = 1;
    appData = applicationData;


    //--------------SDL--------------------------------
    #ifndef SDL_GAME_RENDERER
    #error "SDL_GAME_RENDERER flag is not defined"
    #endif

    
    //Create the Event Handler
    //std::shared_ptr<SDLEventHandler> sdlEventHandlerPtr = std::make_shared<SDLEventHandler>();
    //engineEventHandlerPtr = std::dynamic_pointer_cast<IEventHandler>(sdlEventHandlerPtr);
    bool enventHandlerSuccess = dependencyAppSubSystems.eventHandler.Initialize();
    if(enventHandlerSuccess == false){
        LogManager::Log("GameEngine: Failed to initialize event handler");
        success = -1;
        return success;
    }
    

   
    //TODO: fix this so not setting the rendererdata ptr first.
    //Initialise the window, passing in the sdlrenderdata
    //std::shared_ptr<SDLGameWindow> sdlEngineWindowPtr = std::make_shared<SDLGameWindow>();
    //engineRenderDataPtr->windowPtr = std::dynamic_pointer_cast<IWindow>(sdlEngineWindowPtr);//std::make_shared<SDLGameWindow>(sdlRenderDataPtr);
    bool windowInitSuccess = dependencyAppSubSystems.gameWindow.Initialize(appData->applicationName, appData->windowWidth, appData->windowHeight);
    if(windowInitSuccess == false){
        LogManager::Log("GameEngine: Window failed to initialize");
        success = -1;
        return success;
    }



    bool rendererInitSuccess =  dependencyAppSubSystems.gameRenderer.Initialize(appData->applicationName, appData->windowWidth, appData->windowHeight, &dependencyAppSubSystems.gameWindow);
    if(rendererInitSuccess == false){
        LogManager::Log("GameEngine: Renderer failed to initialize");
        success = -1;
        return success;
    }

    
    bool inputStartSuccess = dependencyAppSubSystems.gameInput.Initialize();
    if(inputStartSuccess == false){
        LogManager::Log("GameEngine: Failed to initialize SDLGameInput");
        success = -1;
        return success;
    }


    //Initialise the Font Renderer
    bool statupSuccess = dependencyAppSubSystems.fontRenderer.Initialize();
    if(statupSuccess == false){
        LogManager::Log("GameEngine: Failed to initialize SDLFontRenderer");
        success = -1;
        return success;
    }

    bool timerStartSuccess = dependencyAppSubSystems.gameTimer.Initialize();
    if(timerStartSuccess == false){
        LogManager::Log("GameEngine: Failed to initialize SDLGameTimer");
        success = -1;
        return success;
    }

   

      //Start the afEngineBehaviours
   if(engineBehaviour == nullptr){//appData->afEngineBehaviourPtr == nullptr){
       LogManager::Log("GameEngine: Engine behaviour is null");
       success = -1;
       return success;
   }else{
        engineBehaviour->awake();
        engineBehaviour->start();
   }

    return success;
}

int GameEngine::loop(const std::shared_ptr<AF_EngineBehaviour> engineBehaviour, DependencyAppSubsystems& dependencyAppSubSystems)
{
    //Update the timer
    dependencyAppSubSystems.gameTimer.start();
    //engineTimer->start();


    //Do a frame for the input and renderer
    dependencyAppSubSystems.gameInput.BeginFrame();
    dependencyAppSubSystems.gameInput.EndFrame();

    //Application will trigger a shutdown once it sees the isRunning flag is false
    if(dependencyAppSubSystems.gameInput.GetIsRunning() == false){
        appData->isRunning = false;
    }

    
    dependencyAppSubSystems.gameWindow.BeginFrame();
    dependencyAppSubSystems.gameWindow.EndFrame();

    //Render the Font Renderer
    dependencyAppSubSystems.fontRenderer.BeginFrame();
    dependencyAppSubSystems.fontRenderer.EndFrame();


    //update the script manager.
    if(engineBehaviour != nullptr){
        engineBehaviour->update();
    }
    else{
        LogManager::Log("GameEngine: Engine behaviour is null");
    }

    //Render the renderer
    dependencyAppSubSystems.gameRenderer.BeginFrame();
    dependencyAppSubSystems.gameRenderer.EndFrame();


    dependencyAppSubSystems.eventHandler.BeginFrame();
    dependencyAppSubSystems.eventHandler.PollEvents(&dependencyAppSubSystems.gameWindow, &dependencyAppSubSystems.gameInput);
    dependencyAppSubSystems.eventHandler.EndFrame();
   

    //
    

    //std::cout << "GameEngine: Frame time: " << (engineTimer->getTicks()) << std::endl;
    //engineTimer->stop();

    //update the games internal frame counter
    dependencyAppSubSystems.gameTimer.countFrameTick();
    dependencyAppSubSystems.gameTimer.stop();

    return 0;
}


//Shutdown
int GameEngine::shutdown(const std::shared_ptr<AF_EngineBehaviour> engineBehaviour, DependencyAppSubsystems& dependencyAppSubSystems)
{
    dependencyAppSubSystems.gameInput.Shutdown();
    
    dependencyAppSubSystems.gameWindow.Shutdown();

    dependencyAppSubSystems.fontRenderer.Shutdown();
    
    dependencyAppSubSystems.gameRenderer.Shutdown();

    //shutdown the game application behaviour
    engineBehaviour->shutdown();

    dependencyAppSubSystems.eventHandler.Shutdown();

    return 0;
}

void GameEngine::requestGameExit(){
    GameEngine::GetInstance()->getAppData()->isRunning = false;
}

AppData *GameEngine::getAppData() 
{
    return appData;
}
GameEngine::GameEngine()
{

}

GameEngine::~GameEngine()
{
    
   
}
