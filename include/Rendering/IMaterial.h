#pragma once
#include <string>
#include "Utils/LogManager.h"
#include "Rendering/IShader.h"
#include <memory>
class IMaterial{
    public:
        virtual bool loadShader(std::string vertexShaderPath, std::string fragmentShaderPath) = 0;
        virtual unsigned int getTexture() = 0;

        virtual const IShader* getShader() const = 0;
        //virtual ~IMaterial() = 0;

};