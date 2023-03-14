#include "LogManager.h"

struct AppData {  
    const char* applicationName;  
    int windowXPos;  
    int windowYPos;  
    int windowWidth;  
    int windowHeight;  
    bool fullscreen;  
};


struct AppSubSystems{
    //MemoryManager* memoryManagerPtr;  
    //TimeManager* timeManagerPtr;  
    //ApplicationStruct* applicationStructPtr;  
    LogManager* logManagerPtr;  
    //InputManager* inputManagerPtr;  
    //SceneManager* sceneManagerPtr;  
    //UIManager* uiManagerPtr;  
    //PhysicsManager* physicsManager;  
    //RendererManager* rendererManager;  
    //ExceptionManager* exceptionManager;  
    //SoundManager* soundManager;  
};

class Application {
    public: 
        AppSubSystems appSubSystem;
        AppData appData;

        Application();
        ~Application();

    private:
        int Startup();
        int Loop();
        int Shutdown();
};
