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

        SDL_Renderer sdlRendererPtr;
        SDL_Surface sdlSurfacePtr;
        // This is a pointer to the SDL2 event.
        std::vector<std::unique_ptr<SDLTexSurfData>> sdlTexSurfList;

    };