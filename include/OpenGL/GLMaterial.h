#define AF_ENGINE_EXPORTS
#ifdef AF_ENGINE_EXPORTS
#define AF_Engine_API __declspec(dllexport)
#else
#define AF_Engine_API __declspec(dllimport)
#endif
#pragma once
#include "Rendering/IMaterial.h"
#include "OpenGL/GL_Shader.h"


class GLMaterial : public IMaterial {
    public:
        //Constructors and destructors
        AF_Engine_API GLMaterial();
        AF_Engine_API ~GLMaterial();

        //getters fore mesh
        GLuint getTexture() override;
        const IShader* getShader() const override;
        void setShader(std::unique_ptr<IShader> thisShader) override;
        AF_Vec4& getMaterialColor() override;
        void setMaterialColor(const AF_Vec4& color) override;
        

    private:

        std::unique_ptr<IShader> shader;
        AF_Vec4 m_color;
};