#pragma once
#include <vector>
#include <memory>
#include "Rendering/AF_MeshType.h"
#include "Rendering/IBuffer_Object.h"

// Mesh class to store reference to a modifiable AF_BaseMesh that becomes a derived version e.g. AF_Quad, AF_Triangle etc. Vertices, Indices stored in the AF_BaseMesh.
//Also stores a generic base class IBuffer_Object which becomes a derived version depending on the rendering engine e.g. OpenGL or DirectX or other. VBO, EBO, VAO stored in the IBuffer_Object.

class AF_Mesh {
public:
    //Constructors and destructors
    AF_Mesh(std::unique_ptr<AF_BaseMesh> thisMesh, std::unique_ptr<IBuffer_Object> thisBufferObject);
    ~AF_Mesh();

    const std::unique_ptr<AF_BaseMesh>& getMesh() const;
    const std::unique_ptr<IBuffer_Object>& getBufferObject() const;


private:
    // Mesh data
    std::unique_ptr<AF_BaseMesh> mesh;
    // Buffer object
    std::unique_ptr<IBuffer_Object> bufferObject;
};
