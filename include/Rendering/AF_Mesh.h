#pragma once
#include <vector>
#include <memory>
#include "Rendering/AF_MeshType.h"

class AF_Mesh {
public:
    //Constructors and destructors
    AF_Mesh(std::unique_ptr<AF_BaseMesh> thisMesh);
    AF_Mesh(std::unique_ptr<AF_BaseMesh> thisMesh, unsigned int thisVAO, unsigned int thisVBO, unsigned int thisEBO);
    ~AF_Mesh();

    const std::unique_ptr<AF_BaseMesh>& getMesh() const;
    //Setters and Getters for VAO, VBO, EBO
    void setVAO(unsigned int thisVAO);
    void setVBO(unsigned int thisVBO);
    void setEBO(unsigned int thisEBO);
    unsigned int getVAO() const;
    unsigned int getVBO() const;
    unsigned int getEBO() const;

private:
    std::unique_ptr<AF_BaseMesh> mesh;
    unsigned int VAO, VBO, EBO;
};
