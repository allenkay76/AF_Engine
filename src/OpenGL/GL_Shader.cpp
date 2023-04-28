#include "OpenGL/GL_Shader.h"
#include <GL/glew.h>


std::string GL_Shader::readFile(std::string thisFilePath){
    std::string line,text;
    std::ifstream in(thisFilePath);
    while(std::getline(in, line))
    {
       text += line + "\n";
    }
    
    return text;
}

GL_Shader::GL_Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	{
        bool success = true;
        //Check if path is empty
        if (vertexShaderPath.empty() || fragmentShaderPath.empty()) {
            LogManager::Log("Unable to load shader as path is missing %s %s\n", vertexShaderPath.c_str(), fragmentShaderPath.c_str());
            success = false;
        }

        //Read vertex shader file
        std::string vertexShaderSource = readFile(vertexShaderPath);
        if (vertexShaderSource.empty()) {
            LogManager::Log("Unable to read vertex shader file %s\n", vertexShaderPath.c_str());
            success = false;
        }
        
        //Read fragment shader file
        std::string fragmentShaderSource = readFile(fragmentShaderPath);
        if (fragmentShaderSource.empty()) {
            LogManager::Log("Unable to read fragment shader file %s\n", fragmentShaderPath.c_str());
            success = false;
        }
        
    //If no errors, create program
    if (success){
        
        //Create program
        setProgramID(glCreateProgram());

        //Create vertex shader
        GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );

        //Set vertex source
        const GLchar* vertexShaderSourcePtr = vertexShaderSource.c_str();
        //Set vertex source
        glShaderSource(vertexShader, 1, &vertexShaderSourcePtr, NULL);

        //Compile vertex source
        glCompileShader(vertexShader);

        //check vertex shader for errors
        GLint vShaderCompiled = GL_FALSE;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
        if(vShaderCompiled != GL_TRUE){
            LogManager::Log("Unable to compile vertex shader %d!\n", vertexShader);
            printShaderLog(vertexShader);
            success = false;
        }
        else{
            //Attach vertex shader to program
            glAttachShader(getProgramID(), vertexShader);

            //Create fragment shader
            GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);


            //Set fragment source
            const GLchar* fragmentShaderSourcePtr = fragmentShaderSource.c_str();
            glShaderSource(fragmentShader, 1, &fragmentShaderSourcePtr, NULL);

            //Compile fragment source
            glCompileShader(fragmentShader);

            //Check fragment shader for errors
            //GLint fShaderCompiled = GL_FALSE;
            //glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
            if(checkCompileErrors(fragmentShader, "SHADER") == false){
                LogManager::Log("Unable to compile fragment shader %d!\n", fragmentShader);
                printShaderLog(fragmentShader);
                success = false;
            }else{

                //Attach fragment shader to program
                glAttachShader(getProgramID(), fragmentShader);

                //Link program
                glLinkProgram(getProgramID());
                
                //Check for errors
                GLint programSuccess = GL_TRUE;
                glGetProgramiv(getProgramID(), GL_LINK_STATUS, &programSuccess);
                if(programSuccess != GL_TRUE){
                    LogManager::Log("Error linking program %d!\n", getProgramID());
                    printProgramLog(getProgramID());
                    success = false;
                }else{
                    //get vertex attribute location
                    setVertexPos2DLocation(glGetAttribLocation(getProgramID(), "LVertexPos2D"));
                    if(getVertexPos2DLocation() == static_cast<GLuint>(-1)){
                        LogManager::Log("LVertexPos2D is not a valid glsl program variable!\n");
                        success = false;
                    }
                }
            }
        }
    }
        LogManager::Log("Shader loaded successfully %s\n", success ? "true" : "false");
    }




    GL_Shader::~GL_Shader()
    {
    }

    // activate the shader
	

    void GL_Shader::use()
    {
		glUseProgram(getID());
	}
	// utility uniform functions
	// ------------------------------------------------------------------------
	void GL_Shader::setBool(const std::string & name, bool value) const
	{
		glUniform1i(glGetUniformLocation(getID(), name.c_str()), (int)value);
	}
	// ------------------------------------------------------------------------
	void GL_Shader::setInt(const std::string & name, int value) const
	{
		glUniform1i(glGetUniformLocation(getID(), name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void GL_Shader::setFloat(const std::string & name, float value) const
	{
		glUniform1f(glGetUniformLocation(getID(), name.c_str()), value);
	}
	// ------------------------------------------------------------------------
    /*
	void setVec2(const std::string & name, const glm::vec2 & value) const
	{
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
    */
	void GL_Shader::setVec2(const std::string & name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(getID(), name.c_str()), x, y);
	}
	// ------------------------------------------------------------------------
    /*
	void setVec3(const std::string & name, const glm::vec3 & value) const
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}*/
	void GL_Shader::setVec3(const std::string & name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(getID(), name.c_str()), x, y, z);
	}
	// ------------------------------------------------------------------------
    /*
	void setVec4(const std::string & name, const glm::vec4 & value) const
	{
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
    */
	void GL_Shader::setVec4(const std::string & name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(getID(), name.c_str()), x, y, z, w);
	}
	// ------------------------------------------------------------------------
    /*
	void setMat2(const std::string & name, const glm::mat2 & mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat3(const std::string & name, const glm::mat3 & mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat4(const std::string & name, const glm::mat4 & mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}*/

	
	// utility function for checking shader compilation/linking errors.
	// ------------------------------------------------------------------------
	bool GL_Shader::checkCompileErrors(const GLuint shader, const std::string type)
	{
        bool returnSuccess = true;
		GLint success;
		GLchar infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "MyEngine::Shader:: ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
                returnSuccess = false;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "MyEngine::Shader:: ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
                returnSuccess = false;
			}
		}
        return returnSuccess;
	}

unsigned int GL_Shader::getID() const
    {
        return ID;
    }

GLuint GL_Shader::getProgramID() const {
    return programID;
}

GLuint GL_Shader::getVertexPos2DLocation() const  {
    return vertexPos2DLocation;
}


void GL_Shader::setProgramID(GLuint thisProgramID)  {
    programID = thisProgramID;
}

void GL_Shader::setVertexPos2DLocation(GLuint thisVertexPos2DLocation) {
    vertexPos2DLocation = thisVertexPos2DLocation;
}



void GL_Shader::printProgramLog(GLuint program){
    //Make sure the name is shader
    if(glIsProgram(program)){
        //Program log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        //Get info string length
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        //Allocate string
        char* infoLog = new char[maxLength];

        //Get info log
        glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
        if(infoLogLength >0){
            //Print Log
            LogManager::Log("%s\n", infoLog);
        }

        //deallocate string
        delete[] infoLog;
    }else{
        LogManager::Log("Name %d is not a program\n", program);
    }
}

void GL_Shader::printShaderLog(GLuint shader){
    //Make sure name is shader
    if(glIsShader(shader)){
        //Shader log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        //Get info string length
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        //Allocate string
        char* infoLog = new char[maxLength];

        //Get info log
        glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
        if(infoLogLength >0){
            //Print Log
            LogManager::Log("%s\n", infoLog);
        }

        //deallocate string
        delete[] infoLog;
    }else{
        LogManager::Log("Name %d is not a shader\n", shader);
    }
}