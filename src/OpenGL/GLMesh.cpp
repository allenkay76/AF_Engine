#include "OpenGL/GLMesh.h"
#include <GL/glew.h>
#include "Math/AF_Math.h"

//GLMesh is a custom open GL mesh class that interits from the IMesh interface
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

AF_Transform& GLMesh::getTransform()
{
    return transform;
}

//getters fore mesh 
const std::unique_ptr<AF_BaseMesh>& GLMesh::getMesh() const
{
    return mesh;
}

//Init the open GL buffers
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

//getters for material
const std::unique_ptr<IMaterial>& GLMesh::getMaterial() const
{
    return material;
}

//render mesh
void GLMesh::renderMesh()
{
   
     GLenum error = GL_NO_ERROR;

    //Bind program
    glUseProgram( getMaterial()->getShader()->getProgramID());

    //Check for error
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "\nglUseProgram %s\n", gluErrorString( error ) );
    }
    //update the shader position
    LogManager::Log("\nLColVal post: %f %i\n" , 1 /getTransform().position.y , getMaterial()->getShader()->getProgramID());
    //getMaterial()->getShader()->setFloat("LColVal", 1 / getTransform().position.y);
    //getMaterial()->getShader()->setVec3("LVertexPos2D", getTransform().position.x, getTransform().position.y, getTransform().position.z);
    int shaderProgram = getMaterial()->getShader()->getProgramID();
    int vertextColorLocation = glGetUniformLocation(getMaterial()->getShader()->getProgramID(), "LColVal");
    //Check for error
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "\nglGetIniformLocation %s\n", gluErrorString( error ) );
    }

    glUniform1f(vertextColorLocation, 1 / getTransform().position.y);//1 / getTransform().position.y);
    //Check for error
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "\nEglUniform1f %s\n", gluErrorString( error ) );
    }

    // Get the location of the projection matrix uniform in the shader
    GLint projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
    //Check for error
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "\nglGetUniformLocation %s\n", gluErrorString( error ) );
    }

    // Create a perspective projection matrix using GLM
    //AF_Mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    const float pi = 3.14159265359f;
    const float fov = 45.0f;
    const float aspectRatio = 800.0f / 600.0f;
    const float nearPlane = 0.1f;
    const float farPlane = 100.0f;

    float tanHalfFov = std::tan(fov * pi / 360.0f);
    float rangeInv = 1.0f / (farPlane - nearPlane);

    AF_Mat4 projectionMatrix;
    projectionMatrix[0][0] = 1.0f / (aspectRatio * tanHalfFov);
    projectionMatrix[1][1] = 1.0f / tanHalfFov;
    projectionMatrix[2][2] = -(farPlane + nearPlane) * rangeInv;
    projectionMatrix[2][3] = -2.0f * farPlane * nearPlane * rangeInv;
    projectionMatrix[3][2] = -1.0f;
    //LogManager::Log("projection matrix: %i %f %f %f %f\n", projectionMatrixLocation , projectionMatrix[0][0], projectionMatrix[1][1], projectionMatrix[2][2], projectionMatrix[3][2]);
    
    // Pass the projection matrix to the shader
    //glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    // Assume the projectionMatrix is a float array with 16 elements
    // Pass the projection matrix to the shader
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, projectionMatrix.data());
    //Check for error
        error = glGetError();
        if( error != GL_NO_ERROR )
        {
            printf( "\nglUniformMatrix4fv %s\n", gluErrorString( error ) );
        }

    

    //in opengl 3.2 Need to create a vao for the mesh and bind it. before calling glenableVertexAttribArray
    //https://stackoverflow.com/questions/24643027/opengl-invalid-operation-following-glenablevertexattribarray
    GLuint gVAO;
    glGenVertexArrays(1, &gVAO);
    glBindVertexArray(gVAO);
    //Check for error
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "\nglEnableVertexAttribArray %s\n", gluErrorString( error ) );
    }

    //Enable vertex position
    glEnableVertexAttribArray( 0);//getMaterial()->getShader()->getVertexPos2DLocation());
    //Check for error
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "\nglEnableVertexAttribArray %s\n", gluErrorString( error ) );
    }


    GLuint gVBO = getBufferObject()->getVBO();
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);

    // Check for error
    error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("OpenGL error: %s\n", gluErrorString(error));
    }
    // Check if the buffer object binding was successful
    if (glGetError() == GL_INVALID_OPERATION) {
        printf("Failed to bind VBO: invalid operation\n");
    }

    glVertexAttribPointer(
        0,//getMaterial()->getShader()->getVertexPos2DLocation(), // index
        2, // size (number of components per vertex attribute)
        GL_FLOAT, // type
        GL_FALSE, // normalized
        2 * sizeof(GLfloat), // stride (byte offset between consecutive vertex attributes)
        0//NULL // offset of the first component
    );

    // Check for error
    error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("OpenGL error: %s\n", gluErrorString(error));
    }
    // Check if the vertex attribute pointer was set up correctly
    if (glGetError() == GL_INVALID_OPERATION) {
        printf("Failed to set up vertex attribute pointer: invalid operation\n");
    }


    //Translate, Rotate, Scale
    //AF_V

    // Set index data and render
    GLuint gIBO = getBufferObject()->getEBO();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);
    //Check for error
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "\nglDrawElements %s\n", gluErrorString( error ) );
    }

    //Disable vertex position
    glDisableVertexAttribArray(getMaterial()->getShader()->getVertexPos2DLocation());

    //Unbind program
    glUseProgram(0);
}

//clean up mesh
void GLMesh::cleanUpMesh(){
    glDeleteProgram( getMaterial()->getShader()->getProgramID());
}

