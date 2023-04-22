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

            // Add the key event to the key event vector.
            addKeyEvent(createKeyEvent(sdlEvent->key.keysym.sym, true));
            if (sdlEvent->key.keysym.sym == SDLK_ESCAPE)
                {
                    LogManager::Log("Escape key pressed: Exiting Application");
                    sdlEventData.sdlEventIsRunning = false;
                }
            break;
            
        case SDL_KEYUP:
            // Set the key down flag to false.
            sdlEventData.sdlEventKeyDown = false;
            // Remove the key event from the key event vector.
            removeKeyEvent(sdlEvent->key.keysym.sym);
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

// Get if a key is pressed
bool SDLGameInput::getKeyPressed()
{
    return sdlEventData.sdlEventKeyDown;
}

// Get the key codes down
const std::vector<std::unique_ptr<AF_KeyEvent>>& SDLGameInput::getKeyEvents() const{
    return *m_keyEvents;
}


// EndFrame function implementation
void SDLGameInput::EndFrame()
{
}


//clear the vector of keyEvents
void SDLGameInput::clearKeyEvents()
{
    m_keyEvents->clear();
}

//create a new keyEvent on the heap
std::unique_ptr<AF_KeyEvent> SDLGameInput::createKeyEvent(int32_t keyCode, bool pressed)
{
    //create a new keyEvent on the heap
    std::unique_ptr<AF_KeyEvent> keyEvent = std::make_unique<AF_KeyEvent>(keyCode, pressed);

    //transfer ownership of the keyEvent to the caller
    return std::move(keyEvent);
}

//add a keyEvent to the vector
void SDLGameInput::addKeyEvent(std::unique_ptr<AF_KeyEvent> keyEvent)
{
    //use emplace_back to avoid copying the keyEvent
    m_keyEvents->emplace_back(std::move(keyEvent));
}

// Remove a key event from the vector
void SDLGameInput::removeKeyEvent(int32_t keyCode)
{
    auto& keyEvents = *m_keyEvents;
    auto it = keyEvents.begin();

    while (it != keyEvents.end()) {
        if ((*it)->keyCode == keyCode) {
            it = keyEvents.erase(it);
        }
        else {
            ++it;
        }
    }
}



//print all keyEvents to the log
void SDLGameInput::printAllKeyEvents(){
    auto& keyEvents = getKeyEvents();
    LogManager::Log("\n events in keyEvents: %d \n", keyEvents.size());
    for (const auto& keyEvent : keyEvents) {
        
        LogManager::Log("\n Key event: %d %d \n", keyEvent->keyCode, keyEvent->keyDown);
    }
}



// Constructor implementation 
/*
Each derived class has its own copy of m_keyEvents, which is separate from the one defined in the abstract base class. 
The derived class can provide its own implementation for the virtual functions that manipulate m_keyEvents, 
which will operate on the copy of m_keyEvents in the derived class.

However, you can initialize the m_keyEvents member in the derived class's constructor by calling the constructor 
of the base class and passing it the initial values of m_keyEvents. 
This will allow the derived class to use the same initial value for m_keyEvents as the base class. For example:
*/
SDLGameInput::SDLGameInput() : IInput(), m_keyEvents(std::make_unique<std::vector<std::unique_ptr<AF_KeyEvent>>>())
{
    //Register the service
    IInputLocator::provide(this);
}

// Destructor implementation
SDLGameInput::~SDLGameInput()
{
    
}
