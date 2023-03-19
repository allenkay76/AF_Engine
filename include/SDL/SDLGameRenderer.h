#pragma once
// This header file includes the interface class for rendering.
#include "GameEngine/IRenderer.h"

// This header file includes SDL2 libraries.
#include <SDL2/SDL.h>

// This preprocessor directive is commented out and provides instructions on how to fix a known issue with SDL2 and main function definition.
//#define SDL_MAIN_HANDLED //https://stackoverflow.com/questions/32342285/undefined-reference-to-winmain16-c-sdl-2/32343111#32343111

// This header file includes the struct to hold render data specific to SDL2 rendering.
#include "SDL/SDLRenderData.h"
#include "Rendering/imageData.h"

// This class inherits from the IRenderer interface class and implements SDL2 rendering functions.
class SDLGameRenderer : public IRenderer {
public:
    // This struct holds the SDL2 specific render data.
    SDLRenderData sdlRenderData;

    // This function initializes the SDL2 window and renderer.
    bool Initialize(const char* windowName, const int windowWidth, const int windowHeight) override;
    // This function shuts down the SDL2 window and renderer.
    void Shutdown() override;
    // This function begins a new rendering frame.
    void BeginFrame() override;
    // This function ends a rendering frame and presents the rendered image.
    void EndFrame() override;

    //Load Media from file path and take in an image data struct pointer, and return true if the image is loaded successfully
    bool loadImage(const char *filePath, ImageData* imageData) override;

    // This is the constructor for the SDLGameRenderer class.
    SDLGameRenderer();
    // This is the destructor for the SDLGameRenderer class.
    ~SDLGameRenderer();
};