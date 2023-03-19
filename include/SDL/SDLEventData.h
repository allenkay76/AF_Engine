// Header guard to ensure this file is included only once in a compilation unit
#pragma once

// Include the SDL2 library
#include <SDL2/SDL.h>

// Define a struct to store SDL event data
struct SDLEventData
{
    SDL_Event sdlEvent; // The SDL event
    bool sdlEventIsRunning; // Flag indicating if the event is still running
};