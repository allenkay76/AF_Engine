#include "SDLGameRenderer.h"

void SDLGameRenderer::Initialize(const char* windowName, const int windowWidth, const int windowHeight)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    sdlData.sdlWindow = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
    sdlData.sdlRenderer = SDL_CreateRenderer(sdlData.sdlWindow, -1, 0);
}

bool SDLGameRenderer::BeginFrame()
{
    bool returnIsRunning = true;
     while (SDL_PollEvent(&sdlData.sdlEvent))
    {
        switch (sdlData.sdlEvent.type)
        {
            case SDL_QUIT:
                returnIsRunning = false;
                break;

            case SDL_KEYDOWN:
                if (sdlData.sdlEvent.key.keysym.sym == SDLK_ESCAPE)
                {
                    returnIsRunning = false;
                }
                break;
        }
    }

    SDL_SetRenderDrawColor(sdlData.sdlRenderer, 255, 0, 0, 255);
    SDL_RenderClear(sdlData.sdlRenderer);

    return returnIsRunning;
}

void SDLGameRenderer::EndFrame()
{
    SDL_RenderPresent(sdlData.sdlRenderer);
}



SDLGameRenderer::SDLGameRenderer()
{
}

SDLGameRenderer::~SDLGameRenderer()
{
}

void SDLGameRenderer::Shutdown()
{
    SDL_DestroyRenderer(sdlData.sdlRenderer);
    SDL_DestroyWindow(sdlData.sdlWindow);
    SDL_Quit();
}
