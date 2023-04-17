#include "SDL/SDLGameWindow.h"
#include "GameEngine/GameEngine.h"
bool SDLGameWindow::Initialize(const char* windowName, const int windowWidth, const int windowHeight){

   //Initialization flag
    bool success = true;
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        // Initialize the SDL library
        LogManager::Log( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Create a new SDL window with the specified dimensions and window name
        //std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window(SDL_CreateWindow(windowName,SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE), SDL_DestroyWindow);
        sdlWindowPtr = std::shared_ptr<SDL_Window>(SDL_CreateWindow(windowName,SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE), SDL_DestroyWindow);
        //sdlRenderDataPtr->sdlWindowPtr = std::move(window);
        if(sdlWindowPtr == nullptr)
        {
            LogManager::Log("SDL window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
    }
    return success;
}

void SDLGameWindow::Shutdown()
{
    

}

void SDLGameWindow::BeginFrame() {
    
    
}


void SDLGameWindow::EndFrame()
{
}

//This function returns a void pointer to the window of SDL_Window type
std::shared_ptr<void> SDLGameWindow::getWindow() {
    return std::static_pointer_cast<void>(sdlWindowPtr); //return a void pointer to the window, we will stat
}

void SDLGameWindow::HandleEvents(const SDL_Event *event)
{
    std::shared_ptr<GameEngine> gameEngine;
    
    switch (event->window.event) {
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            //LogManager::Log("Window size changed to %d x %d", event->window.data1, event->window.data2);
        break;
        
        case SDL_WINDOWEVENT_MINIMIZED:
            LogManager::Log("\nWindow minimized\n");
        
        case SDL_WINDOWEVENT_MAXIMIZED:
            LogManager::Log("\nWindow maximized\n");
        break;
        
        case SDL_WINDOWEVENT_RESTORED:
            //LogManager::Log("Window restored");
        break;
        
        case SDL_WINDOWEVENT_ENTER:
            //LogManager::Log("Mouse entered window");
        break;
        
        case SDL_WINDOWEVENT_LEAVE:
            //LogManager::Log("Mouse left window");
        break;
        
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            //LogManager::Log("Window gained keyboard focus");
        break;
        
        case SDL_WINDOWEVENT_FOCUS_LOST:
            //LogManager::Log("Window lost keyboard focus");
        break;
        
        case SDL_WINDOWEVENT_SHOWN:
            //LogManager::Log("Window shown");
        break;
        
        case SDL_WINDOWEVENT_HIDDEN:
            //LogManager::Log("Window hidden");
        break;
        
        case SDL_WINDOWEVENT_EXPOSED:
            //LogManager::Log("Window exposed");
        break;
        
        case SDL_WINDOWEVENT_MOVED:
            //LogManager::Log("Window moved to %d, %d", event->window.data1, event->window.data2);
        break;
        
        case SDL_WINDOWEVENT_RESIZED:
            //LogManager::Log("Window resized to %d x %d", event->window.data1, event->window.data2);
        break;
        
        case SDL_WINDOWEVENT_CLOSE:
            LogManager::Log("\nWindow close requested\n");
            gameEngine = GameEngine::GetInstance();
            gameEngine->getAppData()->isRunning = false;
            //sdlEventData.sdlEventIsRunning = false;
        break;
        
        case SDL_WINDOWEVENT_TAKE_FOCUS:
            //LogManager::Log("Window is offered a focus");
        break;
        
        case SDL_WINDOWEVENT_HIT_TEST:
            //LogManager::Log("Window has a special hit test");
        break;
        
        default:
            break;
    }
}

bool SDLGameWindow::GetIsRunning()
{
    return false;
}

SDLGameWindow::SDLGameWindow()
{
}

SDLGameWindow::~SDLGameWindow()
{
}
