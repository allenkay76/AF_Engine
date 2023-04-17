#pragma once
#include "GameEngine/IWindow.h"
#include <SDL2/SDL.h>
//#include "Application/AppData.h"
#include "Utils/LogManager.h"
//#include "SDL/SDLRenderData.h"
#include "SDL/SDLEventData.h"    // include the SDLEventData header file

class SDLGameWindow : public IWindow {

public:
    bool Initialize(const char* windowName, const int windowWidth, const int windowHeight) override;
    // This function shuts down the SDL2 window and renderer.
    void Shutdown() override;
    // This function begins a new rendering frame.
    void BeginFrame() override;
    // This function ends a rendering frame and presents the rendered image.
    void EndFrame() override;
    // This function returns whether the application is running.
    bool GetIsRunning() override;

    //This function returns a void pointer to the window of SDL_Window type
    std::shared_ptr<void> getWindow() override;

    void HandleEvents(const SDL_Event* sdlEvent);

    // This is the constructor for the SDLWindow class.
    SDLGameWindow();
    // This is the destructor for the SDLWindow class.
    ~SDLGameWindow();

    
    // This struct holds the SDL2 specific render data.
    //std::shared_ptr<SDLRenderData> sdlRenderDataPtr;

private:
    // This is the SDL2 window.
    std::shared_ptr<SDL_Window> sdlWindowPtr;

    //SDLEventData sdlEventData;        // declare an instance of the SDLEventData struct
};