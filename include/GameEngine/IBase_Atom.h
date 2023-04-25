#pragma once
#include <memory>
class IBase_Atom {
public:
    virtual bool Initialize() = 0;
    virtual void Shutdown() = 0;
    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;
private:
    
};