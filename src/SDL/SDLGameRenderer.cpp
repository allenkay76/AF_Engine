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

#include "Application/DependencyAppSubsystems.h"
//#pragma GCC diagnostic pop



// Define the function to initialize the SDLGameRenderer with a given window name and dimensions
bool SDLGameRenderer::Initialize(const char* windowName, const int windowWidth, const int windowHeight, IWindow* windowPtr)
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

        //use OpenGL 3.1 core
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        
    
        if(windowPtr->getWindow() == nullptr)
        {
            LogManager::Log("SDL window could not be created! SDL_Error: %s %s\n", SDL_GetError(), windowName);
            success = false;
        }
        else
        {
            //set the SDL_Window as we use it all the time
            
            //Save a copy of the window pointer as we will access it a lot. TODO: consider cache coherency as we will be accessing this a lot
            sdlWindowPtr = static_cast<SDL_Window*>(windowPtr->getWindow().get()); //this is the window we will use for the renderer

            // Create a new SDL renderer for the window
            std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> renderer(SDL_CreateRenderer(sdlWindowPtr, -1, 0), SDL_DestroyRenderer);
            sdlRenderDataPtr->sdlRendererPtr = std::move(renderer);
            if(sdlRenderDataPtr->sdlRendererPtr == nullptr)
            {
                LogManager::Log("SDL renderer could not be created! SDL_Error: %s\n", SDL_GetError());
                success = false;
            }

            //std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)> surface(*SDL_GetWindowSurface(sdlRenderData.sdlWindowPtr), SDL_FreeSurface);
            //sdlRenderData.sdlSurfacePtr = std::move(surface);
            sdlRenderDataPtr->sdlSurfacePtr = std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)>(SDL_GetWindowSurface(sdlWindowPtr), SDL_FreeSurface);

            
            if(sdlRenderDataPtr->sdlSurfacePtr == nullptr)
            {
                LogManager::Log("SDL surface could not be created! SDL_Error: %s\n", SDL_GetError());
                success = false;
            }

            //initialise openGL
           // Create an SDL GL context
           sdlRenderDataPtr->sdlContextPtr = SDL_GL_CreateContext(sdlWindowPtr);
            if (!sdlRenderDataPtr->sdlContextPtr) {
                LogManager::Log("SDL_GL_CreateContext failed: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                //Initialize GLEW
                glewExperimental = GL_TRUE; 
                GLenum glewError = glewInit();
                if( glewError != GLEW_OK )
                {
                    LogManager::Log( "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );
                }

                //Use Vsync
                if( SDL_GL_SetSwapInterval( 1 ) < 0 )
                {
                    LogManager::Log( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
                    success = false;
                }

                //Initialize OpenGL
                if( !initGL() )
                {
                    LogManager::Log( "Unable to initialize OpenGL!\n" );
                    success = false;
                }
                glViewport(0, 0, windowWidth, windowHeight);
                //glMatrixMode(GL_PROJECTION);
                //glLoadIdentity();
                gluPerspective(45.0f, (GLfloat)windowWidth / (GLfloat)windowHeight, 0.1f, 100.0f);
                //glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
            }

            
        }
    }

    return success;
}

bool SDLGameRenderer::initGL(){
    bool success = true;
    GLenum error = GL_NO_ERROR;
    
    //Generate Program
    gProgramID = glCreateProgram();

    //Create vertex shader
    GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );

    //Get vertex source
    const GLchar* vertexShaderSource[] =
    {
        "#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"  
    };

    //Set vertex source
    glShaderSource(vertexShader, 1, vertexShaderSource, NULL);

    //Compile vertex source
    glCompileShader(vertexShader);

    //check vertex shader for errors
    GLint vShaderCompiled = GL_FALSE;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
    if(vShaderCompiled != GL_TRUE){
        LogManager::Log("Unable to compile vertex shader %d!\n", vertexShader);
        printShaderLog(vertexShader);
        success = false;
    }
    else{
        //Attach vertex shader to program
        glAttachShader(gProgramID, vertexShader);

        //Create fragment shader
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        //Get fragment source
        const GLchar* fragmentShaderSource[] =
        {
            "#version 140\nout vec4 LFragment; void main() { LFragment = vec4(1.0, 1.0, 1.0, 1.0 ); }"
        };

        //Set fragment source
        glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);

        //Compile fragment source
        glCompileShader(fragmentShader);

        //Check fragment shader for errors
        GLint fShaderCompiled = GL_FALSE;
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
        if(fShaderCompiled != GL_TRUE){
            LogManager::Log("Unable to compile fragment shader %d!\n", fragmentShader);
            printShaderLog(fragmentShader);
            success = false;
        }else{
            //Attach fragment shader to program
            glAttachShader(gProgramID, fragmentShader);

            //Link program
            glLinkProgram(gProgramID);
            
            //Check for errors
            GLint programSuccess = GL_TRUE;
            glGetProgramiv(gProgramID, GL_LINK_STATUS, &programSuccess);
            if(programSuccess != GL_TRUE){
                LogManager::Log("Error linking program %d!\n", gProgramID);
                printProgramLog(gProgramID);
                success = false;
            }else{
                //get vertex attribute location
                gVertexPos2DLocation = glGetAttribLocation(gProgramID, "LVertexPos2D");
                if(gVertexPos2DLocation == static_cast<GLuint>(-1)){
                    LogManager::Log("LVertexPos2D is not a valid glsl program variable!\n");
                    success = false;
                }else{
                    //Initialize clear color
                    glClearColor(0.f, 0.f, 0.f, 1.f);

                    //VBO data
                    GLfloat vertexData[] = {
                        -0.5f, -0.5f,
                        0.5f, -0.5f,
                        0.5f, 0.5f,
                        -0.5f, 0.5f
                    };

                    //IBO data
                    GLuint indexData[] = { 0, 1, 2, 3 };

                    //create VBO
                    glGenBuffers(1, &gVBO);
                    glBindBuffer(GL_ARRAY_BUFFER, gVBO);
                    glBufferData(GL_ARRAY_BUFFER, 2 * 4 *sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

                    //create IBO
                    glGenBuffers(1, &gIBO);
                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
                    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);
                }
            }
        }

    }


    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
    //Check for error
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        success = false;
    }

    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Check for error
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        success = false;
    }
     //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );
    
    //Check for error
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        success = false;
    }
    
    return success;
}



// Define the function to begin a new rendering frame
void SDLGameRenderer::BeginFrame()
{
    
   if(sdlRenderDataPtr->sdlRendererPtr == nullptr){
        LogManager::Log("SDL renderer is null");
        return;
    }
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Bind program
    glUseProgram( gProgramID );

    //Enable vertex position
    glEnableVertexAttribArray( gVertexPos2DLocation );

    //Set vertex data
    glBindBuffer( GL_ARRAY_BUFFER, gVBO );
    glVertexAttribPointer( gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL );

    //Set index data and render
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, gIBO );
    glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL );

    //Disable vertex position
    glDisableVertexAttribArray( gVertexPos2DLocation );

    //Unbind program
    glUseProgram(0);



    
    // Clear the renderer
    //set the background color from the config
    //SDL_SetRenderDrawColor(sdlRenderData.sdlRendererPtr.get(), 50, 50, 100, 255);
    //clear the screen
    //SDL_RenderClear(sdlRenderData.sdlRendererPtr.get());

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
    for(size_t i = 0; i < sdlRenderDataPtr->sdlTexSurfList.size(); i++){
        if(sdlRenderDataPtr->sdlTexSurfList[i]->texturePtr == nullptr){
            LogManager::Log("SDL texture is null");
            return;
        }
        SDL_RenderCopy(sdlRenderDataPtr->sdlRendererPtr.get(), sdlRenderDataPtr->sdlTexSurfList[i]->texturePtr.get(), nullptr, nullptr);
    }
    
    //SDL_RenderCopy(sdlRenderData.sdlRendererPtr, sdlRenderData.sdlTexturePtr, nullptr, nullptr);
    

    // Present the renderer to the window
    //SDL_RenderPresent(sdlRenderData.sdlRendererPtr.get());
    //SDL_GL_SetSwapInterval(1);
    SDL_GL_SwapWindow(sdlWindowPtr);
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
        newTexSurf->texturePtr.reset(SDL_CreateTextureFromSurface(sdlRenderDataPtr->sdlRendererPtr.get(), newTexSurf->surfacePtr.get()));
        //sdlRenderData.sdlTexturePtr = SDL_CreateTextureFromSurface(sdlRenderData.sdlRendererPtr, sdlRenderData.sdlImageSurface);
        if (newTexSurf->texturePtr == nullptr) {
            LogManager::Log("SDL texture failed to create");
            success = false;
        }

        //Add the new texture to the list of textures
        if(success){
            sdlRenderDataPtr->sdlTexSurfList.emplace_back(move(newTexSurf));
        }
    }

    return imageData;
}

void SDLGameRenderer::printProgramLog(GLuint program){
    //Make sure the name is shader
    if(glIsProgram(program)){
        //Program log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        //Get info string length
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        //Allocate string
        char* infoLog = new char[maxLength];

        //Get info log
        glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
        if(infoLogLength >0){
            //Print Log
            LogManager::Log("%s\n", infoLog);
        }

        //deallocate string
        delete[] infoLog;
    }else{
        LogManager::Log("Name %d is not a program\n", program);
    }
}

void SDLGameRenderer::printShaderLog(GLuint shader){
    //Make sure name is shader
    if(glIsShader(shader)){
        //Shader log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        //Get info string length
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        //Allocate string
        char* infoLog = new char[maxLength];

        //Get info log
        glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
        if(infoLogLength >0){
            //Print Log
            LogManager::Log("%s\n", infoLog);
        }

        //deallocate string
        delete[] infoLog;
    }else{
        LogManager::Log("Name %d is not a shader\n", shader);
    }
}



// Define the destructor for the SDLGameRenderer class
SDLGameRenderer::~SDLGameRenderer()
{
}

void SDLGameRenderer::Shutdown()
{
    for (size_t i = 0; i < sdlRenderDataPtr->sdlTexSurfList.size(); i++) {
        SDLTexSurfData* texSurfData = sdlRenderDataPtr->sdlTexSurfList[i].get();
        SDL_FreeSurface(texSurfData->surfacePtr.get());
        SDL_DestroyTexture(texSurfData->texturePtr.get());
    }
    sdlRenderDataPtr->sdlTexSurfList.clear();
    SDL_FreeSurface(sdlRenderDataPtr->sdlSurfacePtr.get());

    SDL_GL_DeleteContext(sdlRenderDataPtr->sdlContextPtr);

    SDL_DestroyRenderer(sdlRenderDataPtr->sdlRendererPtr.get());
    SDL_DestroyWindow(sdlWindowPtr);

    SDL_Quit();
}


