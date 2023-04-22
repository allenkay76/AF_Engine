#include "SDL/SDLEventHandler.h"
#include <SDL2/SDL.h>
#include "SDL/SDLGameInput.h"
#include "SDL/SDLGameWindow.h"

bool SDLEventHandler::Initialize()
{
    
    return true;
}
void SDLEventHandler::Shutdown()
{
    
}

void SDLEventHandler::BeginFrame()
{
}

void SDLEventHandler::EndFrame()
{
}

void SDLEventHandler::PollEvents(IWindow* windowPtr, IInput* inputPtr)
{
    // Cast the input pointer to the SDLGameInput implementation
    SDLGameInput* sdlGameInputPtr = static_cast<SDLGameInput*>(inputPtr);
    //Clear the event queue at the start of the frame
    //sdlGameInputPtr->clearKeyEvents();

    // Cast the window pointer to the SDLGameWindow implementation and get the SDL2 window
    SDLGameWindow* sdlWindowPtr = static_cast<SDLGameWindow*>(windowPtr);
    
    // Poll the SDL2 event queue.
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        //Get the frame events and push them back into the event queue, then loop through the event queue and handle the events
        //GetFrameevents().push_back(sdlEvent);
        // Handle the SDL2 event.
        switch (sdlEvent.type) {
        case SDL_QUIT:
            // Set the isRunning flag to false.
            //sdlEventDataPtr->isRunning = false;
            break;
        case SDL_KEYDOWN:
            // Set the key down flag to true.
            //sdlEventDataPtr->keyDown = true;
            sdlGameInputPtr->HandleEvents(&sdlEvent);
            break;
        case SDL_KEYUP:
            // Set the key down flag to false.
            //sdlEventDataPtr->keyDown = false;
            sdlGameInputPtr->HandleEvents(&sdlEvent);
            break;
        case SDL_MOUSEBUTTONDOWN:
            // Set the mouse button down flag to true.
            //sdlEventDataPtr->mouseButtonDown = true;
            sdlGameInputPtr->HandleEvents(&sdlEvent);
            break;
        case SDL_MOUSEBUTTONUP:
            // Set the mouse button down flag to false.
            //sdlEventDataPtr->mouseButtonDown = false;
            sdlGameInputPtr->HandleEvents(&sdlEvent);
            break;
        case SDL_MOUSEMOTION:
            // Set the mouse position.
            //sdlEventDataPtr->mousePosition.x = sdlEvent.motion.x;
            //sdlEventDataPtr->mousePosition.y = sdlEvent.motion.y;
            sdlGameInputPtr->HandleEvents(&sdlEvent);
            break;
        case SDL_MOUSEWHEEL:
            // Set the mouse wheel position.
            //sdlEventDataPtr->mouseWheelPosition.x = sdlEvent.wheel.x;
            //sdlEventDataPtr->mouseWheelPosition.y = sdlEvent.wheel.y;
            sdlGameInputPtr->HandleEvents(&sdlEvent);
            break;

        case SDL_WINDOWEVENT:
            // Handle the SDL2 window event.
            sdlWindowPtr->HandleEvents(&sdlEvent);
            break;
        default:
            break;
        }
    }

    //Print the key events
    //sdlGameInputPtr->printAllKeyEvents();
    
    
    //GetFrameevents().clear();
}


