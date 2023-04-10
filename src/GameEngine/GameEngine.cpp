#include "GameEngine/GameEngine.h"
#include "Utils/LogManager.h"
#include "SDL/SDLGameWindow.h"
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

/*
GameEngine &GameEngine::GetInstance()
{
    static GameEngine instance;
    return instance;
}
*/

//set the renderer


void GameEngine::setRenderer(IRenderer* renderer)
{
    LogManager::Log("GameEngine: Setting renderer");
    engineRenderer = renderer;
}

//Get the renderer
IRenderer* GameEngine::getRenderer() const
{
    return engineRenderer;
}

//Startup
int GameEngine::startup(AppData* applicationData, const std::shared_ptr<AF_EngineBehaviour> engineBehaviour, DependencyAppSubsystems& dependencyAppSubSystems)
{
    int success = 1;
    LogManager::Log("Dependencies: Starting up: %i", dependencyAppSubSystems.gameTimer.getTicks());
    LogManager::Log("GameEngine: Starting up");
    appData = applicationData;


    //--------------SDL--------------------------------
    #ifndef SDL_GAME_RENDERER
    #error "SDL_GAME_RENDERER flag is not defined"
    #endif


    //Set the renderer and input
    #ifdef SDL_GAME_RENDERER
    //Create the Event Handler
    //std::shared_ptr<SDLEventHandler> sdlEventHandlerPtr = std::make_shared<SDLEventHandler>();
    //engineEventHandlerPtr = std::dynamic_pointer_cast<IEventHandler>(sdlEventHandlerPtr);
    bool enventHandlerSuccess = dependencyAppSubSystems.eventHandler.Initialize();
    if(enventHandlerSuccess == false){
        LogManager::Log("GameEngine: Failed to initialize event handler");
        success = -1;
        return success;
    }
    

    //Create the renderer
    std::shared_ptr<SDLRenderData> sdlRenderDataPtr = std::make_shared<SDLRenderData>();
    engineRenderDataPtr = std::dynamic_pointer_cast<IRenderData>(sdlRenderDataPtr);
    if(engineRenderDataPtr == nullptr){
        LogManager::Log("GameEngine: Failed to cast to IRenderData");
        success = -1;
        return success;
    }
   
    //TODO: fix this so not setting the rendererdata ptr first.
    //Initialise the window, passing in the sdlrenderdata
    std::shared_ptr<SDLGameWindow> sdlEngineWindowPtr = std::make_shared<SDLGameWindow>();
    engineRenderDataPtr->windowPtr = std::dynamic_pointer_cast<IWindow>(sdlEngineWindowPtr);//std::make_shared<SDLGameWindow>(sdlRenderDataPtr);
    bool windowInitSuccess = engineRenderDataPtr->windowPtr->Initialize(appData->applicationName, appData->windowWidth, appData->windowHeight);
    if(windowInitSuccess == false){
        LogManager::Log("GameEngine: Window failed to initialize");
        success = -1;
        return success;
    }


    //Initilise the renderer
    engineRenderer = new SDLGameRenderer(sdlRenderDataPtr); //not a singleton pattern also should
    //SDLGameRenderer* sdlRenderer = dynamic_cast<SDLGameRenderer*>(engineRenderer);
    if (engineRenderer == nullptr) {
        
        // handle the case where the cast fails
        LogManager::Log("GameEngine: Failed to cast to SDLGameRenderer");
        success = -1;
        return success;
    }


    bool rendererInitSuccess = engineRenderer->Initialize(appData->applicationName, appData->windowWidth, appData->windowHeight);
    if(rendererInitSuccess == false){
        LogManager::Log("GameEngine: Renderer failed to initialize");
        success = -1;
        return success;
    }

    //Initialize the input
    //engineInput = new SDLGameInput(); //not a singleton pattern
    
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


    std::shared_ptr<SDLGameTimer> sdlEngineTimer = std::make_shared<SDLGameTimer>();
    engineTimer = std::dynamic_pointer_cast<ITimer>(sdlEngineTimer);
    if(!engineTimer){
        LogManager::Log("GameEngine: Failed to cast to ITimer");
        success = -1;
        return success;
    }
    

    
    #else
    
        LogManager::Log("GameEngine: No renderer defined");
        success = -1;
        return success;
    #endif

    


    

    /*
    m_loadedImage = new ImageData();
    const char* filePath = "../assets/textures/atom_forge_art.png";
    engineRenderer->loadImage(filePath, m_loadedImage);
    */

   //Start the afEngineBehaviours
   if(engineBehaviour == nullptr){//appData->afEngineBehaviourPtr == nullptr){
       LogManager::Log("GameEngine: Engine behaviour is null");
       success = -1;
       return success;
   }else{
        LogManager::Log("GameEngine: Engine behaviour is not null");
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



    if(engineRenderDataPtr->windowPtr == nullptr){
       LogManager::Log("GameEngine: Window is null");
    }else{
        engineRenderDataPtr->windowPtr->BeginFrame();
        engineRenderDataPtr->windowPtr->EndFrame();
    }

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

    //Rendering
    if(engineRenderer == nullptr){
        LogManager::Log("GameEngine: Renderer is null");
        return -1;
    }
    engineRenderer->BeginFrame();
    engineRenderer->EndFrame();


    dependencyAppSubSystems.eventHandler.BeginFrame();
    dependencyAppSubSystems.eventHandler.PollEvents(engineRenderDataPtr->windowPtr.get(), &dependencyAppSubSystems.gameInput);
    dependencyAppSubSystems.eventHandler.EndFrame();
   

    //
    std::string text = "GameEngine: Frame time: "  + std::to_string((dependencyAppSubSystems.gameTimer.getTicks()));
    std::cout << '\r' << std::string(text.length(), ' ') << '\r' << text << std::flush;

    //std::cout << "GameEngine: Frame time: " << (engineTimer->getTicks()) << std::endl;
    //engineTimer->stop();
    dependencyAppSubSystems.gameTimer.stop();

    //LogManager::Log("GameEngine: Frame time: %s" , (engineTimer->getTicks() / 1000.f));
    //free the image data
    //delete imageToLoad->data;
    //delete imageToLoad;
    /**/
    return 0;
}


//Shutdown
int GameEngine::shutdown(const std::shared_ptr<AF_EngineBehaviour> engineBehaviour, DependencyAppSubsystems& dependencyAppSubSystems)
{
    LogManager::Log("GameEngine: Shutting down");
    dependencyAppSubSystems.gameInput.Shutdown();
    
    engineRenderDataPtr->windowPtr->Shutdown();

    dependencyAppSubSystems.fontRenderer.Shutdown();
    
    engineRenderer->Shutdown();

    //shutdown the game application behaviour
    engineBehaviour->shutdown();

    dependencyAppSubSystems.eventHandler.Shutdown();

    //move this later
    delete(m_loadedImage);

    
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
