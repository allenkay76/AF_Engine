#include "OpenGL/GL_BufferObject.h"

    //default constructor
    GL_BufferObject::GL_BufferObject() : VAO(0), VBO(0), EBO(0){

    }

    //destructor
    GL_BufferObject::~GL_BufferObject(){

    }

    //getters and setters
    GLuint GL_BufferObject::getVAO(){
        return VAO;
    }
    GLuint GL_BufferObject::getVBO() {
        return VBO;
    }
    GLuint GL_BufferObject::getEBO() {
        return EBO;
    }
    void GL_BufferObject::setVAO(GLuint thisVAO) {
        VAO = thisVAO;
    }
    void GL_BufferObject::setVBO(GLuint thisVBO) {
        VBO = thisVBO;
    }
    void GL_BufferObject::setEBO(GLuint thisEBO){
        EBO = thisEBO;
    }