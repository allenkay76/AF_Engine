#pragma once
#include <string>
#include "Utils/LogManager.h"
#include "Rendering/IShader.h"
#include <memory>

//Material class to store reference to a modifiable IShader that becomes a derived version e.g. GL_Shader, DX_Shader etc. Texture stored in the IShader.
class IMaterial{
    public:
        virtual unsigned int getTexture() = 0;
        virtual const IShader* getShader() const = 0;
        virtual void setShader(std::unique_ptr<IShader> thisShader) = 0;
        //virtual ~IMaterial() = 0;
};