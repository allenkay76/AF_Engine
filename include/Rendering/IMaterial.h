#pragma once
#include <string>
#include "Utils/LogManager.h"

class IMaterial{
    public:
        virtual bool loadShader(std::string vertexShaderPath, std::string fragmentShaderPath) = 0;
        virtual unsigned int getProgramID() = 0;
        virtual unsigned int getVertexPos2DLocation() = 0;
        virtual unsigned int getTexture() = 0;

        virtual void setProgramID(unsigned int thisProgramID) = 0;
        virtual void setVertexPos2DLocation(unsigned int thisVertexPos2DLocation) = 0;
        virtual void setTexture(unsigned int thisTexture) = 0;

        virtual void printProgramLog(unsigned int program) = 0;
	    virtual void printShaderLog(unsigned int shader) = 0;

        //virtual ~IMaterial() = 0;

};