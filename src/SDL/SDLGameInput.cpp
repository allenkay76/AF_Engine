#include "SDL/SDLGameInput.h"
#include "SDL/SDLEventData.h"

// Initialize function implementation
bool SDLGameInput::Initialize()
{
    // Set the sdlEventIsRunning flag to true
    sdlEventData.sdlEventIsRunning = true;
    return true;
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
    /*
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
    */
}

// GetIsRunning function implementation
bool SDLGameInput::GetIsRunning()
{
    // Return the value of the sdlEventIsRunning flag
    return sdlEventData.sdlEventIsRunning;
}
void SDLGameInput::HandleEvents(const SDL_Event *sdlEvent)
{
    switch (sdlEvent->type) {
        case SDL_QUIT:
            // Set the isRunning flag to false.
            sdlEventData.sdlEventIsRunning = false;
            break;
        case SDL_KEYDOWN:
            // Set the key down flag to true.
            //LogManager::Log("Key down");
            sdlEventData.sdlEventKeyDown = true;
            if (sdlEvent->key.keysym.sym == SDLK_ESCAPE)
                {
                    LogManager::Log("Escape key pressed");
                    sdlEventData.sdlEventIsRunning = false;
                }
            break;
            
        case SDL_KEYUP:
            // Set the key down flag to false.
            sdlEventData.sdlEventKeyDown = false;
            //LogManager::Log("Key up");
            break;
        case SDL_MOUSEBUTTONDOWN:
            // Set the mouse button down flag to true.
            sdlEventData.sdlEventMouseButtonDown = true;
            //LogManager::Log("Mouse down");
            break;
        case SDL_MOUSEBUTTONUP:
            // Set the mouse button down flag to false.
            sdlEventData.sdlEventMouseButtonDown = false;
            //LogManager::Log("Mouse up");
            break;
        case SDL_MOUSEMOTION:
            // Set the mouse position.
            //sdlEventDataPtr->mousePosition.x = sdlEvent.motion.x;
            //sdlEventDataPtr->mousePosition.y = sdlEvent.motion.y;
            //LogManager::Log("Mouse motion %d %d", sdlEvent->motion.x, sdlEvent->motion.y);  
            break;
        case SDL_MOUSEWHEEL:
            // Set the mouse wheel position.
            //sdlEventDataPtr->mouseWheelPosition.x = sdlEvent.wheel.x;
            //sdlEventDataPtr->mouseWheelPosition.y = sdlEvent.wheel.y;
            break;
        default:
            break;
    }
}
bool SDLGameInput::getKeyPressed()
{
    return sdlEventData.sdlEventKeyDown;//gameEngine.dependencyAppSubsystemsPtr.gameInput.sdlEventData.sdlEventKeyDown;
}
bool SDLGameInput::getTestPressed()
{
    return false;
}

// EndFrame function implementation
void SDLGameInput::EndFrame()
{
}


// Default constructor implementation
SDLGameInput::SDLGameInput()
{
    //Register the service
    IInputLocator::provide(this);
}

// Destructor implementation
SDLGameInput::~SDLGameInput()
{
}
