#pragma once

//Base class for all buffer objects
class IBuffer_Object {
public:
    virtual unsigned int getVAO() = 0;
    virtual unsigned int getVBO() = 0;
    virtual unsigned int getEBO() = 0;
    virtual void setVAO(unsigned int thisVAO) = 0;
    virtual void setVBO(unsigned int thisVBO) = 0;
    virtual void setEBO(unsigned int thisEBO) = 0;

    virtual ~IBuffer_Object() = default;

};