#pragma once
#include <string>
#include <iostream>
#include <fstream>



class IShader{
public:
    //virtual IShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) = 0;
    //virtual ~IShader();
    //Getters and setters
    virtual unsigned int getProgramID() const = 0;
    virtual unsigned int getVertexPos2DLocation() const = 0;

    virtual void setProgramID(unsigned int thisProgramID)  = 0;
    virtual void setVertexPos2DLocation(unsigned int thisVertexPos2DLocation)  = 0;

    //Debug functions
    virtual void printProgramLog(unsigned int program) = 0;
	virtual void printShaderLog(unsigned int shader) = 0;

    virtual bool checkCompileErrors(const unsigned int shader, const std::string type) = 0; 
    //edit shader functions
    virtual void use() = 0;
	virtual void setBool(const std::string & name, bool value) const = 0;
	virtual void setInt(const std::string & name, int value) const = 0;
	virtual void setFloat(const std::string & name, float value) const = 0;
	virtual void setVec2(const std::string & name, float x, float y) const = 0;
	virtual void setVec3(const std::string & name, float x, float y, float z) const = 0;
	virtual void setVec4(const std::string & name, float x, float y, float z, float w) = 0;
    virtual unsigned int getID() const = 0;
    virtual std::string readFile(std::string thisFilePath) = 0;
    
};

