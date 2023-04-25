#pragma once
#include <GL/glew.h>
#include "Rendering/IMaterial.h"


class GLMaterial : public IMaterial {
    public:
        //Constructors and destructors
        GLMaterial();
        ~GLMaterial();

        bool loadShader(std::string vertexShaderPath, std::string fragmentShaderPath) override;
        GLuint getProgramID() override;
        GLuint getVertexPos2DLocation() override;
        GLuint getTexture() override;

        void setProgramID(GLuint thisProgramID) override;
        void setVertexPos2DLocation(GLuint thisVertexPos2DLocation) override;
        void setTexture(GLuint thisTexture) override;

        void printProgramLog(unsigned int program) override;
	    void printShaderLog(unsigned int shader) override;

    private:
        GLuint programID;
        GLuint vertexPos2DLocation;
        GLuint texture;
};