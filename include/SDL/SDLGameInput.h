#pragma once
#define AF_ENGINE_EXPORTS
#ifdef AF_ENGINE_EXPORTS
#define AF_Engine_API __declspec(dllexport)
#else
#define AF_Engine_API __declspec(dllimport)
#endif

#include "GameEngine/IInput.h"          // include the IInput header file
#include <SDL2/SDL.h>        // include the SDL2 library
#include "SDL/SDLEventData.h"    // include the SDLEventData header file
#include "Utils/LogManager.h"
//#include "GameEngine/InputSingleton.h"

class SDLGameInput: public IInput{//, public InputSingleton<SDLGameInput> {   // define the SDLGameInput class and inherit from IInput
    //friend class InputSingleton<SDLGameInput>;  // declare the InputSingleton class as a friend class
public:
    

    bool Initialize() override;       // declare the Initialize function, which is a pure virtual function in IInput
    void Shutdown() override;         // declare the Shutdown function, which is a pure virtual function in IInput
    void BeginFrame() override;       // declare the BeginFrame function, which is a pure virtual function in IInput
    void EndFrame() override;         // declare the EndFrame function, which is a pure virtual function in IInput
    bool GetIsRunning() override;     // declare the GetIsRunning function, which is a pure virtual function in IInput

    void HandleEvents(const SDL_Event* sdlEvent);  // declare the HandleEvents function, which is used to handle SDL2 events

    bool getKeyPressed() override;             // declare the GetKeyPressed function, which is used to get whether a key is pressed
    int32_t getKeyCode() override;  // declare the GetKeyCode function, which is used to get the key code of the key that is pressed
    // implement other rendering functions using SDL2 API
    SDLGameInput();                   // declare the constructor for the SDLGameInput class
    ~SDLGameInput();                  // declare the destructor for the SDLGameInput class
    
    void clearKeyEvents() override;
    std::unique_ptr<AF_KeyEvent> createKeyEvent() override;
    void addKeyEvent(std::unique_ptr<AF_KeyEvent> keyEvent) override;
    std::vector<std::unique_ptr<AF_KeyEvent>>& getKeyEvents() override;

private:
    std::vector<std::unique_ptr<AF_KeyEvent>> m_keyEvents;   // declare a vector of AF_KeyEvent structs
    SDLEventData sdlEventData;        // declare an instance of the SDLEventData struct
};