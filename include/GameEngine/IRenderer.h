#pragma once
#define AF_ENGINE_EXPORTS
#ifdef AF_ENGINE_EXPORTS
#define AF_Engine_API __declspec(dllexport)
#else
#define AF_Engine_API __declspec(dllimport)
#endif
#include <memory>
#include "Rendering/imageData.h"
#include "GameEngine/IWindow.h"
#include "Rendering/IMesh.h"
/*
This is an interface class for a rendering engine. 
It provides a set of pure virtual functions that define the basic operations that a renderer must support. 
These functions include initialization and shutdown of the renderer, 
as well as beginning and ending frames for rendering. 
Additional rendering functions can be added as needed by inheriting from this interface class 
and implementing the desired functions.


*/
class IRenderer {
public:
    virtual bool Initialize(const char* windowName, const int windowWidth, const int windowHeight, IWindow* windowPtr) = 0;
    virtual void Shutdown() = 0;
    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;

    //std::unique_ptr<std::vector<std::unique_ptr<AF_BaseMesh>>>
    virtual void addMesh(std::shared_ptr<IMesh> thisBaseMesh) = 0;
    virtual void removeMesh(std::shared_ptr<IMesh> thisBaseMesh) = 0;
    virtual const std::unique_ptr<std::vector<std::shared_ptr<IMesh>>>& getMeshes() const  = 0;
    //Load Media from file path and take in an image data struct pointer, and return true if the image is loaded successfully
    //virtual std::unique_ptr<ImageData> loadImage(const char *filePath) = 0;
    //Load Media from file path
    //virtual bool loadImage(const char* filePath, ImageData* imageData) = 0;
    // add more rendering functions as needed
private:
    std::unique_ptr<std::vector<std::shared_ptr<IMesh>>> m_meshes;
};

/*
In C++, when a member function is declared as "pure virtual" using the "= 0" syntax, 
it means that the function has no implementation in the base class, 
and it must be overridden by derived classes.
This is a way to create an abstract class, which cannot be instantiated directly, 
but can serve as a base class for other classes. 
The idea is that the derived classes must provide their own implementation for the pure virtual functions, 
which allows for polymorphism and dynamic dispatch.
*/


//Null service pattern, initialised in the constructor of inputLocator
class NullIRenderer : public IRenderer {
public:
    virtual bool Initialize(const char* windowName, const int windowWidth, const int windowHeight, IWindow* windowPtr) {
        (void)windowName;
        (void)windowWidth;
        (void)windowHeight;
        (void)windowPtr;
        return false;
    }

    virtual void Shutdown() {}

    virtual void BeginFrame() {}

    virtual void EndFrame() {}

    virtual void addMesh(std::shared_ptr<IMesh> thisBaseMesh) {
        (void)thisBaseMesh;
    }

    virtual void removeMesh(std::shared_ptr<IMesh> thisBaseMesh) {
        (void)thisBaseMesh;
    }


    const std::unique_ptr<std::vector<std::shared_ptr<IMesh>>>& getMeshes() const override {
        static std::unique_ptr<std::vector<std::shared_ptr<IMesh>>> emptyVector = std::make_unique<std::vector<std::shared_ptr<IMesh>>>();
        return emptyVector;
    }
};


//Service Locator Pattern
//https://gameprogrammingpatterns.com/service-locator.html
class IRendererLocator {
private: 
    static IRenderer* m_service;
    static NullIRenderer m_nullService;
    
public:
    static void initialize(); 

    AF_Engine_API static IRenderer* getRenderer(); 

    static void provide(IRenderer* service){
        if(service == nullptr){
            //revert to null service
            m_service = &m_nullService;
        }else{
            m_service = service;
        }
        m_service = service;
    }

};

