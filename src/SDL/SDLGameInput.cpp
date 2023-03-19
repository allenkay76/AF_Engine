#include "SDL/SDLGameInput.h"
#include "SDL/SDLEventData.h"

// Initialize function implementation
void SDLGameInput::Initialize()
{
    // Set the sdlEventIsRunning flag to true
    sdlEventData.sdlEventIsRunning = true;
}

// Shutdown function implementation
void SDLGameInput::Shutdown()
{
    // Set the sdlEventIsRunning flag to false
    sdlEventData.sdlEventIsRunning = false;
}

// BeginFrame function implementation
void SDLGameInput::BeginFrame()
{
    // Loop through all pending events in the event queue
    while (SDL_PollEvent(&sdlEventData.sdlEvent))
    {
        // Handle the event based on its type
        switch (sdlEventData.sdlEvent.type)
        {
            // If the event is a quit event, set the sdlEventIsRunning flag to false
            case SDL_QUIT:
                sdlEventData.sdlEventIsRunning = false;
                break;

            // If the event is a keydown event and the pressed key is the escape key, set the sdlEventIsRunning flag to false
            case SDL_KEYDOWN:
                if (sdlEventData.sdlEvent.key.keysym.sym == SDLK_ESCAPE)
                {
                    sdlEventData.sdlEventIsRunning = false;
                }
                break;
        }
    }
}

// GetIsRunning function implementation
bool SDLGameInput::GetIsRunning()
{
    // Return the value of the sdlEventIsRunning flag
    return sdlEventData.sdlEventIsRunning;
}

// EndFrame function implementation
void SDLGameInput::EndFrame()
{
}

// Default constructor implementation
SDLGameInput::SDLGameInput()
{
}

// Destructor implementation
SDLGameInput::~SDLGameInput()
{
}
