#define AF_ENGINE_EXPORTS
#ifdef AF_ENGINE_EXPORTS
#define AF_Engine_API __declspec(dllexport)
#else
#define AF_Engine_API __declspec(dllimport)
#endif
#include "Rendering/IBuffer_Object.h"
#include <GL/glew.h>


//OpenGL implementation of IBuffer_Object
class GL_BufferObject : public IBuffer_Object {
public:
    //Constructors and destructors
    AF_Engine_API GL_BufferObject();
    ~GL_BufferObject();

    //getters and setters
    GLuint getVAO() override;
    GLuint getVBO() override;
    GLuint getEBO() override;
    void setVAO(GLuint thisVAO) override;
    void setVBO(GLuint thisVBO) override;
    void setEBO(GLuint thisEBO) override;
private:
    // Mesh data
    GLuint VAO, VBO, EBO;   
};