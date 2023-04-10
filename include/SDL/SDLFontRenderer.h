#pragma once
#include "GameEngine/IFontRenderer.h"          // include the IInput header file
#include "Utils/LogManager.h"
//#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_image.h>

class SDLFontRenderer: public IFontRenderer {   // define the SDLGameInput class and inherit from IInput
public:

    bool Initialize() override;       // declare the Initialize function, which is a pure virtual function in IInput
    void Shutdown() override;         // declare the Shutdown function, which is a pure virtual function in IInput
    void BeginFrame() override;       // declare the BeginFrame function, which is a pure virtual function in IInput
    void EndFrame() override;         // declare the EndFrame function, which is a pure virtual function in IInput
    std::unique_ptr<FontData> loadFont(const char *filePath) override;
    // implement other rendering functions using SDL2 API
    SDLFontRenderer();                   // declare the constructor for the SDLGameInput class
    ~SDLFontRenderer();                  // declare the destructor for the SDLGameInput class
};