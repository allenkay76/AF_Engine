#pragma once
#include "GameEngine/IWindow.h"
#include <SDL2/SDL.h>
#include "Application/AppData.h"
#include "Utils/LogManager.h"
#include "SDL/SDLRenderData.h"

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

    // This is the constructor for the SDLWindow class.
    SDLGameWindow();
    // This is the destructor for the SDLWindow class.
    ~SDLGameWindow();

    // This struct holds the SDL2 specific render data.
    std::shared_ptr<SDLRenderData> sdlRenderDataPtr;

private:

};