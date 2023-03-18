#pragma once
#include <SDL.h>

struct SDLData{
        SDL_Window *sdlWindow;
        SDL_Renderer *sdlRenderer;
        SDL_Event sdlEvent;
    };