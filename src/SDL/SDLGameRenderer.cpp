// Include the header file for the SDLGameRenderer class
#include "SDL/SDLGameRenderer.h"

// Define the function to initialize the SDLGameRenderer with a given window name and dimensions
void SDLGameRenderer::Initialize(const char* windowName, const int windowWidth, const int windowHeight)
{
    // Initialize the SDL library
    SDL_Init(SDL_INIT_EVERYTHING);

    // Create a new SDL window with the specified dimensions and window name
    sdlRenderData.sdlWindowPtr = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);

    // Create a new SDL renderer for the window
    sdlRenderData.sdlRendererPtr = SDL_CreateRenderer(sdlRenderData.sdlWindowPtr, -1, 0);
}

// Define the function to begin a new rendering frame
void SDLGameRenderer::BeginFrame()
{
    // Set the rendering draw color to red
    SDL_SetRenderDrawColor(sdlRenderData.sdlRendererPtr, 255, 0, 0, 255);

    // Clear the renderer with the current draw color
    SDL_RenderClear(sdlRenderData.sdlRendererPtr);
}

// Define the function to end a rendering frame and present the renderer on the screen
void SDLGameRenderer::EndFrame()
{

// Present the renderer to the window
SDL_RenderPresent(sdlRenderData.sdlRendererPtr);
}

// Define the constructor for the SDLGameRenderer class
SDLGameRenderer::SDLGameRenderer()
{
}

// Define the destructor for the SDLGameRenderer class
SDLGameRenderer::~SDLGameRenderer()
{
}

// Define the function to shut down the SDLGameRenderer and release any resources
void SDLGameRenderer::Shutdown()
{
    // Destroy the SDL renderer
    SDL_DestroyRenderer(sdlRenderData.sdlRendererPtr);
    // Destroy the SDL window
    SDL_DestroyWindow(sdlRenderData.sdlWindowPtr);

    // Quit the SDL library
    SDL_Quit();
}
