#pragma once
#include "Rendering/IMaterial.h"
#include "OpenGL/GL_Shader.h"

class GLMaterial : public IMaterial {
    public:
        //Constructors and destructors
        GLMaterial();
        ~GLMaterial();

        bool loadShader(std::string vertexShaderPath, std::string fragmentShaderPath) override;

        GLuint getTexture() override;
        const IShader* getShader() const override;
        

    private:
        std::unique_ptr<IShader> shader;
        
};