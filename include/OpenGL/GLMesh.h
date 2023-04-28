#pragma once

#include "Rendering/IMesh.h"

// Mesh class to store reference to a modifiable AF_BaseMesh that becomes a derived version e.g. AF_Quad, AF_Triangle etc. Vertices, Indices stored in the AF_BaseMesh.
//Also stores a generic base class IBuffer_Object which becomes a derived version depending on the rendering engine e.g. OpenGL or DirectX or other. VBO, EBO, VAO stored in the IBuffer_Object.

class GLMesh :  public IMesh {
public:
    //Constructors and destructors
    GLMesh(std::unique_ptr<AF_BaseMesh> thisMesh, std::unique_ptr<IBuffer_Object> thisBufferObject, std::unique_ptr <IMaterial> thisMaterial);
    ~GLMesh();

	bool createShaders() override;
	void initBuffers() override;
    void renderMesh() override;
	void cleanUpMesh() override;

    const std::unique_ptr<AF_BaseMesh>& getMesh() const override;
    const std::unique_ptr<IBuffer_Object>& getBufferObject() const override;
	const std::unique_ptr<IMaterial>& getMaterial() const override;




private:
    // Mesh data
    std::unique_ptr<AF_BaseMesh> mesh;
    // Buffer object
    std::unique_ptr<IBuffer_Object> bufferObject;
	std::unique_ptr<IMaterial> material;
};
