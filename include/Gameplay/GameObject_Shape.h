#pragma once

#include "GameEngine/IGameObject.h"
class GameObject_Shape : public IGameObject
{
public:
    GameObject_Shape();
    ~GameObject_Shape();

    void awake() override;
    void start() override;
    void update() override;
    void render() override;
    void shutdown() override;


    AF_Transform& getTransform() override;
    IMesh& getMesh() override;

private:
    std::unique_ptr<AF_Transform> m_transform;
    std::unique_ptr<IMesh> m_mesh;
    //shader(vertexPath, fragmentPath)
    //texture(imagePath)
    //material(shader, texture)
    //mesh(material, vertices, indices)
    //game object(mesh, transform)
};