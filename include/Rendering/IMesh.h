#pragma once
#include <vector>
#include <memory>
#include "Rendering/AF_MeshType.h"
#include "Rendering/IBuffer_Object.h"
#include "Rendering/IMaterial.h"

// Mesh class to store reference to a modifiable AF_BaseMesh that becomes a derived version e.g. AF_Quad, AF_Triangle etc. Vertices, Indices stored in the AF_BaseMesh.
//Also stores a generic base class IBuffer_Object which becomes a derived version depending on the rendering engine e.g. OpenGL or DirectX or other. VBO, EBO, VAO stored in the IBuffer_Object.

class IMesh {
public:
    //Constructors and destructors
    //virtual IMesh(std::unique_ptr<AF_BaseMesh> thisMesh, std::unique_ptr<IBuffer_Object> thisBufferObject) = 0;
    //virtual ~IMesh() = 0;

    virtual bool createShaders() = 0;
    virtual void initBuffers() = 0;
    virtual void renderMesh() = 0;
    virtual void cleanUpMesh() = 0;
    

    virtual const std::unique_ptr<AF_BaseMesh>& getMesh() const = 0;
    virtual const std::unique_ptr<IBuffer_Object>& getBufferObject() const = 0;
    virtual const std::unique_ptr<IMaterial>& getMaterial() const = 0;


private:
    // Mesh data
    //std::unique_ptr<AF_BaseMesh> mesh;
    // Buffer object
    //std::unique_ptr<IBuffer_Object> bufferObject;
};
