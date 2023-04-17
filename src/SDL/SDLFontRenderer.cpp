#include "SDL/SDLFontRenderer.h"

bool SDLFontRenderer::Initialize()
{
    
    return true;
}
void SDLFontRenderer::Shutdown()
{
    
}

void SDLFontRenderer::BeginFrame()
{
    //LogManager::Log("SDLFontRenderer::BeginFrame()");
}

void SDLFontRenderer::EndFrame()
{
    //LogManager::Log("SDLFontRenderer::EndFrame()");
}
std::unique_ptr<FontData> SDLFontRenderer::loadFont(const char *filePath)
{
    LogManager::Log("SDLFontRenderer::loadFont %s", filePath);
    return std::unique_ptr<FontData>();
}

SDLFontRenderer::SDLFontRenderer()
{
    
}

SDLFontRenderer::~SDLFontRenderer()
{
    
}
