#include "GameEngine/IEventHandler.h"
#include "Utils/LogManager.h"
#include <SDL2/SDL.h>
#include "SDL/SDLGameInput.h"
#include "SDL/SDLGameWindow.h"

class SDLEventHandler : public IEventHandler
{
public:
    void Initialize() override;
    void Shutdown() override;
    void BeginFrame() override;
    void EndFrame() override;
    
    void PollEvents( IWindow* windowPtr,  IInput* inputPtr) override;
};
