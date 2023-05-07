#include "Gameplay/GameObject_Shape.h"
#include "GameEngine/IRenderer.h"


IRenderer* rendererService = nullptr;


//Constructor
GameObject_Shape::GameObject_Shape() : m_transform(std::make_unique<AF_Transform>()), m_mesh(nullptr)
{
    rendererService = IRendererLocator::getRenderer();
}

//Destructor
GameObject_Shape::~GameObject_Shape()
{

}

// Called first
void GameObject_Shape::awake()
{
    //m_transform->position = AF_Vec3(0.0f, 0.0f, 0.0f);
    //m_transform->rotation = AF_Vec3(0.0f, 0.0f, 0.0f);
    //m_transform->scale = AF_Vec3(1.0f, 1.0f, 1.0f);
   
}

// Called second
void GameObject_Shape::start()
{
    //m_mesh->setMaterial();
    //m_mesh->setVertices();
    //m_mesh->setIndices();
}

// Called third in the game loop
void GameObject_Shape::update()
{
    if(m_mesh != nullptr){
        //m_transform->position = AF_Vec3(0.0f, 0.0f, 0.0f);
        //m_transform->rotation = AF_Vec3(0.0f, 0.0f, 0.0f);
        //m_transform->scale = AF_Vec3(1.0f, 1.0f, 1.0f);
        m_mesh->getTransform().position = m_transform->position;
        m_mesh->getTransform().rotation = m_transform->rotation;
        m_mesh->getTransform().scale = m_transform->scale;

        //LogManager::Log("\nLColVal pre: %f\n" , m_transform->position.y);
    }
}

// Called fourth in the game loop after Update
void GameObject_Shape::render()
{
    
    m_mesh->renderMesh();
}

// Called last outside of the game loop
void GameObject_Shape::shutdown()
{
}

AF_Transform& GameObject_Shape::getTransform()
{
    return *m_transform.get();
}

IMesh& GameObject_Shape::getMesh()
{
    return *m_mesh.get();
}


void GameObject_Shape::setMesh(std::shared_ptr<IMesh> thisMesh)
{
    m_mesh = thisMesh;
    rendererService->addMesh(thisMesh);
}
