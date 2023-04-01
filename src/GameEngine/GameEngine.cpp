#include "GameEngine/GameEngine.h"
#include "Utils/LogManager.h"
#include "SDL/SDLGameRenderer.h"
#include "SDL/SDLGameInput.h"
#include "GameEngine/AF_EngineBehaviour.h"


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
int GameEngine::startup(AppData* applicationData, const std::shared_ptr<AF_EngineBehaviour> engineBehaviour)
{
    int success = 1;
    LogManager::Log("GameEngine: Starting up");
    appData = applicationData;
    //Set the game engine pointer in the app data
    //appData->gameEnginePtr = this;

    //This should be wrapped in if def for SDL
    engineRenderer = new SDLGameRenderer(); //not a singleton pattern also should
    engineInput = new SDLGameInput(); //not a singleton pattern


    
    //Initialize the renderer
    bool rendererInitSuccess = engineRenderer->Initialize(appData->applicationName, appData->windowWidth, appData->windowHeight);
    if(rendererInitSuccess == false){
        LogManager::Log("GameEngine: Renderer failed to initialize");
        success = -1;
        return success;
    }

    //Initialize the input
    engineInput->Initialize();

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

int GameEngine::loop(const std::shared_ptr<AF_EngineBehaviour> engineBehaviour)
{
    //Do a frame for the input and renderer
    engineInput->BeginFrame();
    engineInput->EndFrame();

    //Application will trigger a shutdown once it sees the isRunning flag is false
    if(engineInput->GetIsRunning() == false){
        appData->isRunning = false;
    }

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
    

    //free the image data
    //delete imageToLoad->data;
    //delete imageToLoad;
    /**/
    return 0;
}


//Shutdown
int GameEngine::shutdown(const std::shared_ptr<AF_EngineBehaviour> engineBehaviour)
{
    LogManager::Log("GameEngine: Shutting down");
    engineInput->Shutdown();
    engineRenderer->Shutdown();

    //shutdown the game application behaviour
    engineBehaviour->shutdown();

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
