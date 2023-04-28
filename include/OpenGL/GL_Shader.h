#pragma once
#include <GL/glew.h>
#include "Rendering/IShader.h"
#include <string>
#include "Utils/LogManager.h"
//#include <glad/glad.h> // include glad to get all the required OpenGL headers



class GL_Shader : public IShader
{
public:
    //Constructors and destructors
    GL_Shader(const std::string&  vertexShaderPath, const std::string & fragmentShaderPath);
    ~GL_Shader();

    GLuint getProgramID() const override;
    GLuint getVertexPos2DLocation() const override;

    void setProgramID(GLuint thisProgramID)  override;
    void setVertexPos2DLocation(GLuint thisVertexPos2DLocation)  override;

    void printProgramLog(GLuint program) override;
	void printShaderLog(GLuint shader) override;

    bool checkCompileErrors(const GLuint shader, const std::string type) override;
    void use() override;
	void setBool(const std::string & name, bool value) const override;
	void setInt(const std::string & name, int value) const override;
	void setFloat(const std::string & name, float value) const override;
	void setVec2(const std::string & name, float x, float y) const override;
	void setVec3(const std::string & name, float x, float y, float z) const override;
	void setVec4(const std::string & name, float x, float y, float z, float w) override;
    unsigned int getID() const override;
    std::string readFile(std::string thisFilePath) override;
private:
	unsigned int ID;
    GLuint programID;
    GLuint vertexPos2DLocation;
    GLuint texture;
};
