#pragma once
#include "Rendering/IMesh.h"
#include "GameEngine/AF_Transform.h"

class IGameObject {
public:
    //virtual ~IGameObject() = 0;
    virtual void awake() = 0;
    virtual void start() = 0;
    virtual void render() = 0;
    virtual void update() = 0;
    virtual void shutdown() = 0;
    virtual AF_Transform& getTransform() = 0;
    virtual IMesh& getMesh() = 0;

    virtual void setMesh(std::shared_ptr<IMesh> thisMesh) = 0;

};
