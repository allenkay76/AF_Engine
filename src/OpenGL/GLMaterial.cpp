#include "OpenGL/GLMaterial.h"

//Constructors 
GLMaterial::GLMaterial() : shader(nullptr)
{
    //std::string vert = "./assets/shaders/basicUnlit.vs";
    //std::string frag = "./assets/shaders/basicUnlit.fs";
    //shader = std::make_unique<GL_Shader>(vert, frag);

}

//Destructor
GLMaterial::~GLMaterial() {
}

//Take a IShader smart pointer and assign it to the shader member using move 
void GLMaterial::setShader(std::unique_ptr<IShader> thisShader){
    shader = std::move(thisShader);
}

//Return the shader member pointer
const IShader* GLMaterial::getShader() const{
    return shader.get();
}

//TODO implement this function
GLuint GLMaterial::getTexture(){
    LogManager::Log("TODO implement GLMaterial::getTexture()");
    return 0;
}


