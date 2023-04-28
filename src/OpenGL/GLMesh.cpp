#include "OpenGL/GLMesh.h"
#include <GL/glew.h>
//partial constructor, only mesh data passed in and using std::move to transfer ownership
GLMesh::GLMesh(std::unique_ptr<AF_BaseMesh> thisMesh, std::unique_ptr<IBuffer_Object> thisBufferObject, std::unique_ptr<IMaterial> thisMaterial) : 
    mesh(std::move(thisMesh)),
    bufferObject(std::move(thisBufferObject)),
    material(std::move(thisMaterial))
{
    
} 


//destructor
GLMesh::~GLMesh()
{
}

//getters fore mesh 
const std::unique_ptr<AF_BaseMesh>& GLMesh::getMesh() const
{
    return mesh;
}

bool GLMesh::createShaders(){
    bool success = true;
    //GLenum error = GL_NO_ERROR;
    
    getMaterial()->loadShader("","");
    return success;
}

void GLMesh::initBuffers()
{
    GLuint gVBO, gIBO;
    glGenBuffers(1, &gVBO);
    glGenBuffers(1, &gIBO);

    glBindBuffer(GL_ARRAY_BUFFER, gVBO);
    glBufferData(GL_ARRAY_BUFFER, getMesh()->getVerticesArrayMemorySize(), getMesh()->getVerticesData(), GL_STATIC_DRAW);

    // Bind the IBO and set the buffer data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, getMesh()->getIndicesArrayMemorySize(), getMesh()->getIndicesData(), GL_STATIC_DRAW);

    // Set the VBO and IBO values in the BufferObject object
    //auto bufferObject = std::move(mesh.getBufferObject());
    getBufferObject()->setVBO(gVBO);
    getBufferObject()->setEBO(gIBO);

}

//getters for buffer object
const std::unique_ptr<IBuffer_Object>& GLMesh::getBufferObject() const
{
    return bufferObject;
}

const std::unique_ptr<IMaterial>& GLMesh::getMaterial() const
{
    return material;
}

void GLMesh::renderMesh()
{
    //Bind program
    glUseProgram( getMaterial()->getShader()->getProgramID());
    //Enable vertex position
    glEnableVertexAttribArray( getMaterial()->getShader()->getVertexPos2DLocation());

    GLuint gVBO = getBufferObject()->getVBO();
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);
    glVertexAttribPointer(getMaterial()->getShader()->getVertexPos2DLocation(), 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

    // Set index data and render
    GLuint gIBO = getBufferObject()->getEBO();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

    //Disable vertex position
    glDisableVertexAttribArray(getMaterial()->getShader()->getVertexPos2DLocation());

    //Unbind program
    glUseProgram(0);
}

void GLMesh::cleanUpMesh(){
    glDeleteProgram( getMaterial()->getShader()->getProgramID());
}

