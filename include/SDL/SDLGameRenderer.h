#pragma once
#include <memory>
#include <SDL2/SDL.h>



// This header file includes SDL2 libraries.

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
// This header file includes the interface class for rendering.
#include "GameEngine/IRenderer.h"
// This preprocessor directive is commented out and provides instructions on how to fix a known issue with SDL2 and main function definition.
//#define SDL_MAIN_HANDLED //https://stackoverflow.com/questions/32342285/undefined-reference-to-winmain16-c-sdl-2/32343111#32343111

// This header file includes the struct to hold render data specific to SDL2 rendering.
#include "SDL/SDLRenderData.h"
#include "Rendering/imageData.h"

// This class inherits from the IRenderer interface class and implements SDL2 rendering functions.
class SDLGameRenderer : public IRenderer {


public:
    
    
    // This struct holds the SDL2 specific render data.
    std::shared_ptr<SDLRenderData> sdlRenderDataPtr;
    SDL_Window* sdlWindowPtr;

    //graphics program
    GLuint gProgramID = 0;
    GLuint gVertexPos2DLocation = -1;
    GLuint gVBO = 0;
    GLuint gIBO = 0;
    GLuint gTexture = 0;

    // This function initializes the SDL2 window and renderer.
    bool Initialize(const char* windowName, const int windowWidth, const int windowHeight, IWindow* windowPtr) override;
    bool InitializeSDLRenderer(const char* windowName, const int windowWidth, const int windowHeight, const std::shared_ptr<SDLRenderData> thisSDLRenderData);
    // This function shuts down the SDL2 window and renderer.
    void Shutdown() override;
    // This function begins a new rendering frame.
    void BeginFrame() override;
    // This function ends a rendering frame and presents the rendered image.
    void EndFrame() override;

    bool initGL(); //Initialize OpenGL
    
    //Load Media from file path and take in an image data struct pointer, and return true if the image is loaded successfully
    std::unique_ptr<ImageData> loadImage(const char *filePath) override;

    //Shader loading utility programs
    void printProgramLog(GLuint program);
    void printShaderLog(GLuint shader);

    // This is the constructor for the SDLGameRenderer class.
    SDLGameRenderer(std::shared_ptr<SDLRenderData> renderDataPtr) : sdlRenderDataPtr(renderDataPtr){};
    // This is the destructor for the SDLGameRenderer class.
    ~SDLGameRenderer();

    
};