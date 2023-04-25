#include "OpenGL/GLMaterial.h"

//Constructors and destructors

GLMaterial::GLMaterial() : 
    programID(0),
    vertexPos2DLocation(0),
    texture(0)
{
}

GLMaterial::~GLMaterial() {
}

// 
bool GLMaterial::loadShader(std::string vertexShaderPath, std::string fragmentShaderPath){
    bool success = true;
    if (vertexShaderPath.length() < 1 || fragmentShaderPath.length() < 1){
        LogManager::Log("Unable to load shader as path is missing %s %s\n", vertexShaderPath.c_str(), fragmentShaderPath.c_str());
        success = false;
    }
    //Generate Program
    setProgramID(glCreateProgram());

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
        glAttachShader(getProgramID(), vertexShader);

        //Create fragment shader
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        //Get fragment source
        const GLchar* fragmentShaderSource[] =
        {
            "#version 140\nout vec4 LFragment; void main() { LFragment = vec4(1.0, 0.5, 0.2, 1.0 ); }"
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
            glAttachShader(getProgramID(), fragmentShader);

            //Link program
            glLinkProgram(getProgramID());
            
            //Check for errors
            GLint programSuccess = GL_TRUE;
            glGetProgramiv(getProgramID(), GL_LINK_STATUS, &programSuccess);
            if(programSuccess != GL_TRUE){
                LogManager::Log("Error linking program %d!\n", getProgramID());
                printProgramLog(getProgramID());
                success = false;
            }else{
                //get vertex attribute location
                setVertexPos2DLocation(glGetAttribLocation(getProgramID(), "LVertexPos2D"));
                if(getVertexPos2DLocation() == static_cast<GLuint>(-1)){
                    LogManager::Log("LVertexPos2D is not a valid glsl program variable!\n");
                    success = false;
                }
            }
        }
    }
    return success;
}

GLuint GLMaterial::getProgramID() {
    return programID;
}

GLuint GLMaterial::getVertexPos2DLocation() {
    return vertexPos2DLocation;
}

GLuint GLMaterial::getTexture() {
    return texture;
}

void GLMaterial::setProgramID(GLuint thisProgramID) {
    programID = thisProgramID;
}

void GLMaterial::setVertexPos2DLocation(GLuint thisVertexPos2DLocation) {
    vertexPos2DLocation = thisVertexPos2DLocation;
}

void GLMaterial::setTexture(GLuint thisTexture) {
    texture = thisTexture;
}


void GLMaterial::printProgramLog(GLuint program){
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

void GLMaterial::printShaderLog(GLuint shader){
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
