#pragma once
#include "GameEngine/IGameObject.h"
#define AF_ENGINE_EXPORTS
#ifdef AF_ENGINE_EXPORTS
#define AF_Engine_API __declspec(dllexport)
#else
#define AF_Engine_API __declspec(dllimport)
#endif

// AF_EngineBehaviour is the base class for all game objects
class AF_Engine_API AF_EngineBehaviour : public IGameObject {
public:
    
    virtual void awake() override;
    virtual void start() override;
    virtual void update()override;
    virtual void shutdown() override;

    AF_EngineBehaviour ();
    virtual ~AF_EngineBehaviour ();

private:
};
