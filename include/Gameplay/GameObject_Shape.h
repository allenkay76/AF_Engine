#pragma once
#define AF_ENGINE_EXPORTS
#ifdef AF_ENGINE_EXPORTS
#define AF_Engine_API __declspec(dllexport)
#else
#define AF_Engine_API __declspec(dllimport)
#endif
#include "GameEngine/IGameObject.h"
class GameObject_Shape : public IGameObject
{
public:
    AF_Engine_API GameObject_Shape();
    AF_Engine_API ~GameObject_Shape();

    void awake() override;
    void start() override;
    void update() override;
    void render() override;
    void shutdown() override;


    AF_Transform& getTransform() override;
    IMesh& getMesh() override;
    void setMesh(std::shared_ptr<IMesh> thisMesh) override;

private:
    std::unique_ptr<AF_Transform> m_transform;
    std::shared_ptr<IMesh> m_mesh;
    //shader(vertexPath, fragmentPath)
    //texture(imagePath)
    //material(shader, texture)
    //mesh(material, vertices, indices)
    //game object(mesh, transform)
};