#pragma once
#include <memory>

#include "Rendering/fontData.h"

class IFontRenderer {
public:
    virtual bool Initialize() = 0;
    virtual void Shutdown() = 0;
    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;

    //Load Media from file path and take in an image data struct pointer, and return true if the image is loaded successfully
    virtual std::unique_ptr<FontData> loadFont(const char *filePath) = 0;
    //Load Media from file path
    //virtual bool loadImage(const char* filePath, ImageData* imageData) = 0;
    // add more rendering functions as needed
};