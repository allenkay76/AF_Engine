#pragma once
#include <SDL2/SDL.h>

struct SDLRenderData{
        SDL_Window *sdlWindowPtr;  //pointer to sdlWindow
        SDL_Renderer *sdlRendererPtr;  //pointer to sdlRenderer
    };