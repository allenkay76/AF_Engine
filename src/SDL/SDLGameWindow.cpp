#include "SDL/SDLGameWindow.h"

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
        std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window(SDL_CreateWindow(windowName,SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE), SDL_DestroyWindow);
        sdlRenderDataPtr->sdlWindowPtr = std::move(window);
        if(sdlRenderDataPtr->sdlWindowPtr == nullptr)
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

void SDLGameWindow::BeginFrame()
{
}

void SDLGameWindow::EndFrame()
{
}

bool SDLGameWindow::GetIsRunning()
{
    return false;
}


SDLGameWindow::~SDLGameWindow()
{
}
