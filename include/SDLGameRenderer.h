#include "IRenderer.h"
#include <SDL2/SDL.h>
//#define SDL_MAIN_HANDLED //https://stackoverflow.com/questions/32342285/undefined-reference-to-winmain16-c-sdl-2/32343111#32343111
#include "SDLData.h"

class SDLGameRenderer : public IRenderer {
public:
    SDLData sdlData;

    void Initialize(const char* windowName, const int windowWidth, const int windowHeight) override;
    void Shutdown() override;
    bool BeginFrame() override;
    void EndFrame() override;
    //void DrawRectangle() override;//int x, int y, int w, int h) override;
    // implement other rendering functions using SDL2 API
    SDLGameRenderer();
    ~SDLGameRenderer();
};
