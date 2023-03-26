// Include the header file for the SDLGameRenderer class
#include "SDL/SDLGameRenderer.h"
#include "Utils/LogManager.h"
#include "Rendering/imageData.h"

//need to do this as we trust the stb_image.h library but our compiler settings treat warnings as errors.
//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wconversion"
#define STB_IMAGE_IMPLEMENTATION
#include "Utils/stb_image.h"

#include "SDL/SDLTexSurfData.h"
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
        LogManager::Log( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Create a new SDL window with the specified dimensions and window name
        std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window(SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0), SDL_DestroyWindow);
        sdlRenderData.sdlWindowPtr = std::move(window);
        if(sdlRenderData.sdlWindowPtr == nullptr)
        {
            LogManager::Log("SDL window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Create a new SDL renderer for the window
            std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> renderer(SDL_CreateRenderer(sdlRenderData.sdlWindowPtr.get(), -1, 0), SDL_DestroyRenderer);
            sdlRenderData.sdlRendererPtr = std::move(renderer);
            if(sdlRenderData.sdlRendererPtr == nullptr)
            {
                LogManager::Log("SDL renderer could not be created! SDL_Error: %s\n", SDL_GetError());
                success = false;
            }

            //std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)> surface(*SDL_GetWindowSurface(sdlRenderData.sdlWindowPtr), SDL_FreeSurface);
            //sdlRenderData.sdlSurfacePtr = std::move(surface);
            sdlRenderData.sdlSurfacePtr = std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)>(SDL_GetWindowSurface(sdlRenderData.sdlWindowPtr.get()), SDL_FreeSurface);

            
            if(sdlRenderData.sdlSurfacePtr == nullptr)
            {
                LogManager::Log("SDL surface could not be created! SDL_Error: %s\n", SDL_GetError());
                success = false;
            }
        }
    }

    return success;
}



// Define the function to begin a new rendering frame
void SDLGameRenderer::BeginFrame()
{
    
   if(sdlRenderData.sdlRendererPtr == nullptr){
        LogManager::Log("SDL renderer is null");
        return;
    }
    // Clear the renderer
    //set the background color from the config
    SDL_SetRenderDrawColor(sdlRenderData.sdlRendererPtr.get(), 50, 50, 100, 255);
    //clear the screen
    SDL_RenderClear(sdlRenderData.sdlRendererPtr.get());

    //Work thrugh a list of render commands to draw things to the screen.
    // Render any sprites or other game objects here
    // Render the image using the renderer

    
  
    /**/
    /*
    //Loading of an image
    sdlRenderData.imagePtr = new ImageData();
    const char* filePath = "assets/textures/atom_forge_art.png";
    loadSDLImage(filePath, sdlRenderData.imagePtr);
    */
    
    
}

void SDLGameRenderer::EndFrame()
{
    /*
    int imgWidth = sdlRenderData.sdlImageSurface->w;
    int imgHeight = sdlRenderData.sdlImageSurface->h;
    SDL_Rect dstRect = { (sdlRenderData.imagePtr->width - imgWidth) / 2, (sdlRenderData.imagePtr->height - imgHeight) / 2, imgWidth, imgHeight };
    */
    //SDL_RenderCopy(sdlRenderData.sdlRendererPtr, sdlRenderData.sdlTexturePtr, nullptr, &dstRect);
    for(size_t i = 0; i < sdlRenderData.sdlTexSurfList.size(); i++){
        if(sdlRenderData.sdlTexSurfList[i]->texturePtr == nullptr){
            LogManager::Log("SDL texture is null");
            return;
        }
        SDL_RenderCopy(sdlRenderData.sdlRendererPtr.get(), sdlRenderData.sdlTexSurfList[i]->texturePtr.get(), nullptr, nullptr);
    }
    
    //SDL_RenderCopy(sdlRenderData.sdlRendererPtr, sdlRenderData.sdlTexturePtr, nullptr, nullptr);
                
    // Present the renderer to the window
    SDL_RenderPresent(sdlRenderData.sdlRendererPtr.get());
}



std::unique_ptr<ImageData> SDLGameRenderer::loadImage(const char *filePath)
{
    std::unique_ptr<ImageData> imageData (new ImageData());
    //Initialization flag
    bool success = true;
    LogManager::Log("Attempting to load image %s!\n", filePath);

    int width, height, channels;
    unsigned char* imageBits = stbi_load(filePath, &width, &height, &channels, STBI_rgb_alpha);
    if (imageBits == nullptr) {
        LogManager::Log("Error loading image: %s\n", stbi_failure_reason());
        LogManager::Log("Unable to load image %s!\n", filePath);

        success = false;
    } else {
        LogManager::Log("Loaded image: %s (%d x %d x %d)", filePath, width, height, channels);
        imageData->width = width;
        imageData->height = height;
        imageData->channels = channels;
        imageData->data = imageBits;

        //Create a surface from the image data
        std::unique_ptr<SDLTexSurfData> newTexSurf(new SDLTexSurfData());


        newTexSurf->surfacePtr.reset(SDL_CreateRGBSurfaceFrom(imageData->data, imageData->width, imageData->height, 32, 4 * imageData->width, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000));
        //sdlRenderData.sdlImageSurface = SDL_CreateRGBSurfaceFrom(imageData->data,imageData->width, imageData->height, 32, 4 * imageData->width, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
        if (newTexSurf->surfacePtr == nullptr) {
            LogManager::Log("Unable to create SDL surface for image %s!\n", filePath);
            stbi_image_free(imageData->data);
            success = false ;
        }

        LogManager::Log("SDLGameRenderer: Creating texture from surface");
        //Create a texture from the surface
        newTexSurf->texturePtr.reset(SDL_CreateTextureFromSurface(sdlRenderData.sdlRendererPtr.get(), newTexSurf->surfacePtr.get()));
        //sdlRenderData.sdlTexturePtr = SDL_CreateTextureFromSurface(sdlRenderData.sdlRendererPtr, sdlRenderData.sdlImageSurface);
        if (newTexSurf->texturePtr == nullptr) {
            LogManager::Log("SDL texture failed to create");
            success = false;
        }

        //Add the new texture to the list of textures
        if(success){
            sdlRenderData.sdlTexSurfList.emplace_back(move(newTexSurf));
        }
    }

    return imageData;
}



// Define the constructor for the SDLGameRenderer class
SDLGameRenderer::SDLGameRenderer()
{
}

// Define the destructor for the SDLGameRenderer class
SDLGameRenderer::~SDLGameRenderer()
{
}

void SDLGameRenderer::Shutdown()
{
    for (size_t i = 0; i < sdlRenderData.sdlTexSurfList.size(); i++) {
        SDLTexSurfData* texSurfData = sdlRenderData.sdlTexSurfList[i].get();
        SDL_FreeSurface(texSurfData->surfacePtr.get());
        SDL_DestroyTexture(texSurfData->texturePtr.get());
    }
    sdlRenderData.sdlTexSurfList.clear();
    SDL_FreeSurface(sdlRenderData.sdlSurfacePtr.get());
    SDL_DestroyRenderer(sdlRenderData.sdlRendererPtr.get());
    SDL_DestroyWindow(sdlRenderData.sdlWindowPtr.get());

    SDL_Quit();
}


