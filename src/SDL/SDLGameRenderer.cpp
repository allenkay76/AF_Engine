// Include the header file for the SDLGameRenderer class
#include "SDL/SDLGameRenderer.h"
#include "SDL/SDLGameRenderer.h"
#include "Utils/LogManager.h"
#include "Rendering/imageData.h"

//need to do this as we trust the stb_image.h library but our compiler settings treat warnings as errors.
//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wconversion"
#define STB_IMAGE_IMPLEMENTATION
#include "Utils/stb_image.h"
//#pragma GCC diagnostic pop

// Define the function to initialize the SDLGameRenderer with a given window name and dimensions
bool SDLGameRenderer::Initialize(const char* windowName, const int windowWidth, const int windowHeight)
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        // Initialize the SDL library
        //SDL_Init(SDL_INIT_EVERYTHING);
        LogManager::Log( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }else{
        // Create a new SDL window with the specified dimensions and window name
        sdlRenderData.sdlWindowPtr = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
        if(sdlRenderData.sdlWindowPtr == NULL){
            LogManager::Log("SDL window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }else{
            // Create a new SDL renderer for the window
            sdlRenderData.sdlRendererPtr = SDL_CreateRenderer(sdlRenderData.sdlWindowPtr, -1, 0);
            if(sdlRenderData.sdlRendererPtr == NULL){
                LogManager::Log("SDL renderer could not be created! SDL_Error: %s\n", SDL_GetError());
                success = false;
            }

            sdlRenderData.sdlSurfacePtr = SDL_GetWindowSurface(sdlRenderData.sdlWindowPtr);
            if(sdlRenderData.sdlSurfacePtr == NULL){
                LogManager::Log("SDL surface could not be created! SDL_Error: %s\n", SDL_GetError());
                success = false;
            }
        }
    }


    //Loading of an image
    sdlRenderData.imagePtr = new ImageData();
    const char* filePath = "assets/textures/atom_forge_art.png";
    
    bool imageLoadSuccess = loadImage(filePath, sdlRenderData.imagePtr);
    if(imageLoadSuccess == false){
        LogManager::Log("Unable to load image %s!\n", filePath);
        success = false;
    }

    sdlRenderData.sdlImageSurface = SDL_CreateRGBSurfaceFrom(sdlRenderData.imagePtr->data, sdlRenderData.imagePtr->width, sdlRenderData.imagePtr->height, 32, 4 * sdlRenderData.imagePtr->width, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
    if (sdlRenderData.sdlImageSurface == nullptr) {
        LogManager::Log("Unable to create surface for image %s!\n", filePath);
        stbi_image_free(sdlRenderData.imagePtr->data);
        success = false ;
    }
    return success;
}

// Define the function to begin a new rendering frame
void SDLGameRenderer::BeginFrame()
{
    // Clear the renderer
    //set the background color from the config
    SDL_SetRenderDrawColor(sdlRenderData.sdlRendererPtr, 50, 50, 100, 255);
    SDL_RenderClear(sdlRenderData.sdlRendererPtr);

    //Work thrugh a list of render commands to draw things to the screen.
    // Render any sprites or other game objects here
    // Render the image using the renderer
    SDL_Texture* texture = SDL_CreateTextureFromSurface(sdlRenderData.sdlRendererPtr, sdlRenderData.sdlImageSurface);
    if (texture != nullptr) {
        int imgWidth = sdlRenderData.sdlImageSurface->w;
        int imgHeight = sdlRenderData.sdlImageSurface->h;
        SDL_Rect dstRect = { (sdlRenderData.imagePtr->width - imgWidth) / 2, (sdlRenderData.imagePtr->height - imgHeight) / 2, imgWidth, imgHeight };
        SDL_RenderCopy(sdlRenderData.sdlRendererPtr, texture, nullptr, &dstRect);
        SDL_DestroyTexture(texture);
    }

    // Present the renderer to the window
    SDL_RenderPresent(sdlRenderData.sdlRendererPtr);
    
}

// Define the function to end a rendering frame and present the renderer on the screen
void SDLGameRenderer::EndFrame()
{

    
}

// Function to load an image from a file path and take an existing ImageData struct that is already defined and return a pointer to the ImageData struct
bool SDLGameRenderer::loadImage(const char *filePath, ImageData* imageData)
{
    LogManager::Log("Loading image %s %s!\n", filePath, imageData->width);
    
    int width, height, channels;
    unsigned char* imageBits = stbi_load(filePath, &width, &height, &channels, STBI_rgb_alpha);
    if (imageBits == nullptr) {
        LogManager::Log("Error loading image: ", stbi_failure_reason());
        return false;
    }else{
        imageData->width = width;
        imageData->height = height;
        imageData->channels = channels;
        imageData->data = imageBits;
        return true;
    }
    /**/
   return false;
}

// Define the constructor for the SDLGameRenderer class
SDLGameRenderer::SDLGameRenderer()
{
}

// Define the destructor for the SDLGameRenderer class
SDLGameRenderer::~SDLGameRenderer()
{
}

// Define the function to shut down the SDLGameRenderer and release any resources
void SDLGameRenderer::Shutdown()
{

    //Free the surface
    SDL_FreeSurface( sdlRenderData.sdlSurfacePtr );
    SDL_FreeSurface( sdlRenderData.sdlImageSurface );
    
    //free the image data
    delete sdlRenderData.imagePtr->data;
    delete sdlRenderData.imagePtr;

    // Destroy the SDL renderer
    SDL_DestroyRenderer(sdlRenderData.sdlRendererPtr);
    // Destroy the SDL window
    SDL_DestroyWindow(sdlRenderData.sdlWindowPtr);

    

    // Quit the SDL library
    SDL_Quit();
}
