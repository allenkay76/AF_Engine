#include "Rendering/AF_Mesh.h"

//Full values passed inconstructor
AF_Mesh::AF_Mesh(std::unique_ptr<AF_BaseMesh> thisMesh, unsigned int thisVAO, unsigned int thisVBO, unsigned int thisEBO) : 
    mesh(std::move(thisMesh)),
    VAO(thisVAO), 
    VBO(thisVBO), 
    EBO(thisEBO) {

} 

//partial constructor
AF_Mesh::AF_Mesh(std::unique_ptr<AF_BaseMesh> thisMesh) : mesh(std::move(thisMesh)), VAO(0), VBO(0), EBO(0){
    
} 


//destructor
AF_Mesh::~AF_Mesh()
{
}

const std::unique_ptr<AF_BaseMesh>& AF_Mesh::getMesh() const
{
    return mesh;
}


// return reference to mesh data
void AF_Mesh::setVAO(unsigned int thisVAO)
{
    this->VAO = thisVAO;
}

// return reference to mesh data
void AF_Mesh::setVBO(unsigned int thisVBO)
{
    this->VBO = thisVBO;
}

// return reference to mesh data
void AF_Mesh::setEBO(unsigned int thisEBO)
{
    this->EBO = thisEBO;
}

// return const reference to VAO
unsigned int AF_Mesh::getVAO() const
{
    return VAO;
}

// return const reference to VBO
unsigned int AF_Mesh::getVBO() const
{
    return VBO;
}

// return const reference to EBO
unsigned int AF_Mesh::getEBO() const
{
    return EBO;
}



