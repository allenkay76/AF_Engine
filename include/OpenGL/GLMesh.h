#define AF_ENGINE_EXPORTS
#ifdef AF_ENGINE_EXPORTS
#define AF_Engine_API __declspec(dllexport)
#else
#define AF_Engine_API __declspec(dllimport)
#endif

#pragma once
#include "Rendering/IMesh.h"

// Mesh class to store reference to a modifiable AF_BaseMesh that becomes a derived version e.g. AF_Quad, AF_Triangle etc. Vertices, Indices stored in the AF_BaseMesh.
//Also stores a generic base class IBuffer_Object which becomes a derived version depending on the rendering engine e.g. OpenGL or DirectX or other. VBO, EBO, VAO stored in the IBuffer_Object.

class GLMesh :  public IMesh {
public:
    //Constructors and destructors
    AF_Engine_API GLMesh(std::unique_ptr<AF_BaseMesh> thisMesh, std::unique_ptr<IBuffer_Object> thisBufferObject, std::unique_ptr <IMaterial> thisMaterial);
    AF_Engine_API ~GLMesh();

    //SEtup functions for mesh
	void initBuffers() override;
    void renderMesh() override;
	void cleanUpMesh() override;

    //getters for mesh
    const std::unique_ptr<AF_BaseMesh>& getMesh() const override;
    const std::unique_ptr<IBuffer_Object>& getBufferObject() const override;
	const std::unique_ptr<IMaterial>& getMaterial() const override;

    AF_Transform& getTransform() override;


private:
    // Mesh data
    std::unique_ptr<AF_BaseMesh> mesh;
    // Buffer object
    std::unique_ptr<IBuffer_Object> bufferObject;
	std::unique_ptr<IMaterial> material;

    AF_Transform transform;
};
