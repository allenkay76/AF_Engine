#include "GameEngine/IEventHandler.h"
#include "GameEngine/IInput.h"
#include "Utils/LogManager.h"


class SDLEventHandler : public IEventHandler
{
public:
    bool Initialize() override;
    void Shutdown() override;
    void BeginFrame() override;
    void EndFrame() override;
    
    void PollEvents( IWindow* windowPtr,  IInput* inputPtr) override;
};
