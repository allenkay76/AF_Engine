#include "GameEngine/GameEngine.h"
#include "Utils/LogManager.h"
#include "GameEngine/ScriptManager.h"
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
    engineRenderer = new SDLGameRenderer(); //not a singleton pattern also should
    engineInput = new SDLGameInput(); //not a singleton pattern


    
    //Initialize the renderer
    bool rendererInitSuccess = engineRenderer->Initialize(appData->applicationName, appData->windowWidth, appData->windowHeight);
    if(rendererInitSuccess == false){
        LogManager::Log("GameEngine: Renderer failed to initialize");
        return -1;
    }

    //Initialize the input
    engineInput->Initialize();

    /*
    m_loadedImage = new ImageData();
    const char* filePath = "../assets/textures/atom_forge_art.png";
    engineRenderer->loadImage(filePath, m_loadedImage);
    */

   //Start the afEngineBehaviours
   if(appData->afEngineBehaviourPtr == nullptr){
       LogManager::Log("GameEngine: Engine behaviour is null");
       return -1;
   }else{
        LogManager::Log("GameEngine: Engine behaviour is not null");
        appData->afEngineBehaviourPtr->awake();
        appData->afEngineBehaviourPtr->start();
   }
  
    return 1;
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

    //update the script manager.
    if(appData->afEngineBehaviourPtr != nullptr){
        appData->afEngineBehaviourPtr->update();
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

    //Loading of an image
   
    
     /**/


    engineRenderer->EndFrame();
    

    //free the image data
    //delete imageToLoad->data;
    //delete imageToLoad;
    /**/
    return 0;
}

//Shutdown
int GameEngine::shutdown()
{
    LogManager::Log("GameEngine: Shutting down");
    
    engineInput->Shutdown();
    engineRenderer->Shutdown();

    //shutdown the game application behaviour
    appData->afEngineBehaviourPtr->shutdown();


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
