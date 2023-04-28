#include "OpenGL/GLMaterial.h"

//Constructors and destructors

GLMaterial::GLMaterial() 
    
{
    std::string vert = "./assets/shaders/basicUnlit.vs";
    std::string frag = "./assets/shaders/basicUnlit.fs";
    shader = std::make_unique<GL_Shader>(vert, frag);

}

GLMaterial::~GLMaterial() {
}

// 
bool GLMaterial::loadShader(std::string vertexShaderPath, std::string fragmentShaderPath){
    bool success = true;
    //getShader()->loadShader(vertexShaderPath, fragmentShaderPath);
    LogManager::Log("GLMaterial::loadShader: No Longer Loading Shaders in GLMaterial %s %s ", vertexShaderPath.c_str(), fragmentShaderPath.c_str());
    return success;
}

const IShader* GLMaterial::getShader() const{
    return shader.get();
}

GLuint GLMaterial::getTexture(){
    return 0;
}


