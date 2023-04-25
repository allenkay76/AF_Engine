#include "Rendering/AF_Mesh.h"



//partial constructor, only mesh data passed in and using std::move to transfer ownership
AF_Mesh::AF_Mesh(std::unique_ptr<AF_BaseMesh> thisMesh, std::unique_ptr<IBuffer_Object> thisBufferObject) : 
    mesh(std::move(thisMesh)),
    bufferObject(std::move(thisBufferObject))
{
    
} 


//destructor
AF_Mesh::~AF_Mesh()
{
}

//getters fore mesh 
const std::unique_ptr<AF_BaseMesh>& AF_Mesh::getMesh() const
{
    return mesh;
}

//getters for buffer object
const std::unique_ptr<IBuffer_Object>& AF_Mesh::getBufferObject() const
{
    return bufferObject;
}
