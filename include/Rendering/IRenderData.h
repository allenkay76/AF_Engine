#pragma once
#include <memory>
#include "GameEngine/IWindow.h"
#include "GameEngine/IRenderer.h"
#include "ImageData.h"

struct IRenderData {
    virtual ~IRenderData() {}

    IWindow windowPtr;
    IRenderer rendererPtr;
    ImageData imagePtr;
};