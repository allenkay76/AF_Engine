#pragma once
#include <memory>
#include "GameEngine/IWindow.h"
#include "GameEngine/IInput.h"

class IEventHandler {
public:
    virtual bool Initialize() = 0;
    virtual void Shutdown() = 0;
    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;
    
    virtual void PollEvents( IWindow* windowPtr,  IInput* inputPtr) = 0;
};
