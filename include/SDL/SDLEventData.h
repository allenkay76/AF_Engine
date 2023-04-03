// Header guard to ensure this file is included only once in a compilation unit
#pragma once

// Include the SDL2 library
#include <SDL2/SDL.h>

// Define a struct to store SDL event data
struct SDLEventData
{
    bool sdlEventIsRunning; // Flag indicating if the event is still running
    bool sdlEventKeyDown; // Flag indicating if a key is down
    bool sdlEventMouseButtonDown; // Flag indicating if a mouse button is down
    SDL_Point sdlEventMousePosition; // The mouse position

};