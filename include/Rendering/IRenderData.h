#pragma once
#include <memory>
#include "GameEngine/IWindow.h"
#include "GameEngine/IRenderer.h"
#include "ImageData.h"

struct IRenderData {
    virtual ~IRenderData() {}

    std::shared_ptr<IWindow> windowPtr;
    std::unique_ptr<IRenderer> rendererPtr;
    std::unique_ptr<ImageData> imagePtr;
};