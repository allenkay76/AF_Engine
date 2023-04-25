// Include the header file for the SDLGameRenderer class
#include "SDL/SDLGameRenderer.h"
#include "Utils/LogManager.h"

#include "OpenGL/GLMesh.h"
#include "Rendering/AF_MeshType.h"  
#include "OpenGL/GL_BufferObject.h"
#include "OpenGL/GLMaterial.h"
//#include "Rendering/imageData.h"


//need to do this as we trust the stb_image.h library but our compiler settings treat warnings as errors.
//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wconversion"
#define STB_IMAGE_IMPLEMENTATION
#include "Utils/stb_image.h"

//#include "SDL/SDLTexSurfData.h"

//#include "Application/DependencyAppSubsystems.h"
//#include "SDLGameRenderer.h"
//#pragma GCC diagnostic pop

std::unique_ptr<IMaterial> testMaterial;
std::unique_ptr<IMesh> testMesh;
std::unique_ptr<IBuffer_Object> testBufferObject;
std::unique_ptr<AF_BaseMesh> quadMesh;

// Define the function to initialize the SDLGameRenderer with a given window name and dimensions
bool SDLGameRenderer::Initialize(const char* windowName, const int windowWidth, const int windowHeight, IWindow* windowPtr)
{
    //Initialization flag
    bool success = true;
    
    CreateTestMesh();

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
            sdlGameWindowPtr = static_cast<SDL_Window*>(windowPtr->getWindow().get()); //this is the window we will use for the renderer


            //initialise openGL
           // Create an SDL GL context
            sdlGameGLContext  = SDL_GL_CreateContext(sdlGameWindowPtr);
            if (sdlGameGLContext == NULL) {
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
                //set the glViewport and the perspective
                glViewport(0, 0, windowWidth, windowHeight);\
                gluPerspective(45.0f, (GLfloat)windowWidth / (GLfloat)windowHeight, 0.1f, 100.0f);
                glLoadIdentity();
            }

            
        }
    }

    

    return success;
}

// Define the function to render the SDLGameRenderer. Do all the init things
bool SDLGameRenderer::initGL(){
    bool success = true;
    GLenum error = GL_NO_ERROR;


    // Get the meshes from the vector and store them in a variable
    auto meshes = getMeshes().get();
    // Generate VBO and IBO objects for each mesh
    for (const auto& meshPtr : *meshes) {
        if (meshPtr == nullptr) {
            LogManager::Log("\nMesh is null\n");
                continue;
            }
        // Get the mesh from the unique_ptr
        auto& mesh = *meshPtr;
        bool shaderSuccess = false;
        // Create the shader program
        shaderSuccess = mesh.createShaders();
        if(shaderSuccess == false)
        {
            // Break the initGL loop if we fail to create a shader
            LogManager::Log("\nShader creation failed\n");
            success = false;
            break;
        }

        // Create the VBO and IBO objects
        mesh.initBuffers();
    }

    
    //Check for error
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "\nError initializing OpenGL! after shader and buffer init %s\n", gluErrorString( error ) );
        success = false;
    }

    //Initialize clear color
    glClearColor(0.f, 0.f, 0.f, 1.f);
                    
    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
    //Check for error
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "\nError initializing OpenGL! after glMatrixMode/loadIdentify %s\n", gluErrorString( error ) );
        success = false;
    }

    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Check for error
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "\nError initializing OpenGL! after loading model view %s\n", gluErrorString( error ) );
        success = false;
    }
     //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );
    
    //Check for error
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "\nError initializing OpenGL! after clear color for last time %s\n", gluErrorString( error ) );
        success = false;
    }
    
    return success;
}



// Define the function to begin a new rendering frame
void SDLGameRenderer::BeginFrame()
{   
    // Clear the screen
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 
   // Loop through the meshes and set the buffer data
   // Get the meshes from the vector and store them in a variable
    auto meshes = getMeshes().get();

    // Loop through the meshes tell to render
    for (const auto& meshPtr : *meshes) {
        if (meshPtr == nullptr) {
            LogManager::Log("Mesh is null");
                continue;
                }

            auto& mesh = *meshPtr;
            mesh.renderMesh();
    }
 
    
}

// Define the function to end a rendering frame
void SDLGameRenderer::EndFrame()
{
    // Swap the buffers
    SDL_GL_SwapWindow(sdlGameWindowPtr);
}


// Define the function to shutdown the renderer
void SDLGameRenderer::Shutdown()
{
    //Cleanup all the meshes
    auto meshes = getMeshes().get();
    for (const auto& meshPtr : *meshes) {
        if (meshPtr == nullptr) {
            LogManager::Log("Mesh is null");
                continue;
                }

            auto& mesh = *meshPtr;
            mesh.cleanUpMesh();
    }

    // Destroy the context
    SDL_GL_DeleteContext(sdlGameGLContext);
    // Destroy the SDL
    SDL_Quit();
}

// Define the function to add a mesh
void SDLGameRenderer::addMesh(std::unique_ptr<IMesh> thisMesh) {
    if(thisMesh == nullptr){
        LogManager::Log("SDLGameRenderer::addMesh: Mesh is null");
        return;
    }
    m_meshes->emplace_back(move(thisMesh));
}

// Define the function to remove a mesh
void SDLGameRenderer::removeMesh(std::unique_ptr<IMesh> thisMesh) {
    LogManager::Log("SDLGameRenderer::removeMesh: Not implemented");
    if(thisMesh == nullptr){
        LogManager::Log("SDLGameRenderer::removeMesh: Mesh is null");
        return;
    }
    
}

// Define the function to get the meshes
const std::unique_ptr<std::vector<std::unique_ptr<IMesh>>>& SDLGameRenderer::getMeshes() const {
    
    return m_meshes;
}

void SDLGameRenderer::CreateTestMesh(){
    //Create the mesh vector
    m_meshes = std::make_unique<std::vector<std::unique_ptr<IMesh>>>();
    //Create the mesh
    quadMesh = std::make_unique<AF_Quad>();
    testBufferObject = std::make_unique<GL_BufferObject>();
    testMaterial = std::make_unique<GLMaterial>();
    // Create the mesh, ensure we transfer ownership of the mesh to the IMesh object
    // need to also pass in the derived openGL buffer object which is derived from IBuffer_Object. This way we can swap from opegl to other standards
    testMesh = std::make_unique<GLMesh>(std::move(quadMesh), std::move(testBufferObject), std::move(testMaterial));
    addMesh(std::move(testMesh));
}

// Define the destructor for the SDLGameRenderer class
SDLGameRenderer::SDLGameRenderer()
{
    //just init the pointers to null
    sdlGameWindowPtr = nullptr;
}
// Define the destructor for the SDLGameRenderer class
SDLGameRenderer::~SDLGameRenderer()
{
}




