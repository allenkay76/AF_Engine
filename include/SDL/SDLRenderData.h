#pragma once
#include <memory>
#include <vector>

#include <SDL2/SDL.h>
#include "SDL/SDLTexSurfData.h"
#include "Rendering/IRenderdata.h"


using namespace std;
//TODO convert to constructor struct so values are initialized to 0
struct SDLRenderData : public IRenderData {
        //std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> sdlWindowPtr{nullptr, &SDL_DestroyWindow}; 
        //std::shared_ptr<SDLGameWindow> sdlWindowPtr;
        SDL_GLContext sdlContextPtr;

        std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> sdlRendererPtr{nullptr, &SDL_DestroyRenderer};
        std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> sdlSurfacePtr{nullptr, &SDL_FreeSurface};
        // This is a pointer to the SDL2 event.
        std::vector<std::unique_ptr<SDLTexSurfData>> sdlTexSurfList;

    };