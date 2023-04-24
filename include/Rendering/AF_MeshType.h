#pragma once
#include <cstring>
#include "Utils/LogManager.h"

// This is a base mesh class that will be inherited by other mesh classes
// This class will be used to store the vertices and indices data, the size of the vertices and indices data
class AF_BaseMesh
{
public:
    virtual ~AF_BaseMesh() {}

    //Get the vertices data array
    //const float* getVerticesData() const { return verticesData.get(); }
    //Get the indices data array
    //const unsigned int* getIndicesData() const { return indexData.get(); }
    const float* getVerticesData() const { return verticesData.get(); }
    const unsigned int* getIndicesData() const { return indexData.get(); }


    //Get the size of the array at compile time
    static constexpr size_t getVerticesArraySize() { return verticesArraySize; }
    //Get the size of the vertices array memory at compile time
    static constexpr size_t getVerticesArrayMemorySize() { return verticesArrayMemorySize; }

    //Get the size of the array at compile time
    static constexpr size_t getIndicesArraySize() { return indicesArraySize;}
    //Get the size of the indices array memory at compile time
    static constexpr size_t getIndicesArrayMemorySize() { return indicesArrayMemorySize;}

protected:
    

    // our quad is an x,y so 2 elements. save this at compile time using constexpr
    static constexpr size_t elementSize = 2;
    static constexpr size_t verticesAmount = 4;

    // stord values for the size and memory required to use the quad
    static constexpr size_t verticesArraySize = elementSize * verticesAmount;
    static constexpr size_t verticesArrayMemorySize = verticesArraySize * sizeof(float);

    static constexpr size_t indicesArraySize = 4;
    static constexpr size_t indicesArrayMemorySize = indicesArraySize * sizeof(unsigned int);

    std::unique_ptr<float[]> verticesData = nullptr;// = std::make_unique<float[]>(verticesArraySize);
    std::unique_ptr<unsigned int[]> indexData = nullptr; //= std::make_unique<unsigned int[]>(indicesArraySize);


    //float verticesData[verticesArraySize];
    //unsigned int indexData[indicesArraySize];
};

// This is a quad class that inherits from the base mesh class
class AF_Quad : public AF_BaseMesh
{
public:
    AF_Quad()
    {
        verticesData = std::unique_ptr<float[]>(new float[verticesArraySize]);
        indexData = std::unique_ptr<unsigned int[]>(new unsigned int[indicesArraySize]);

        // initialize the vertices data array
        float vertices[] = {
            -0.5f, -0.5f,
             0.5f, -0.5f,
             0.5f,  0.5f,
            -0.5f,  0.5f
        };
        std::memcpy(verticesData.get(), vertices, sizeof(vertices));
        LogManager::Log("AF_Quad::AF_Quad() verticesData[1] = %f", verticesData[1]);

        // initialize the index data array
        unsigned int indices[] = { 0, 1, 2, 3 };
        std::memcpy(indexData.get(), indices, sizeof(indices));
    }
};



/*
float verticesData[verticesArraySize] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    unsigned int indexData[indicesArraySize] = { 0, 1, 2, 3 };
*/


struct AF_Triangle
{
    float verticies [6]={
        -0.5f, -0.5f, 
        0.5f, -0.5f,
        0.5f, 0.5f
    };
};


struct AF_Cube{
    float verticies [24]={
        -0.5f, -0.5f, -0.5f, 
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f, 
        -0.5f, 0.5f, -0.5f,

        -0.5f, -0.5f, 0.5f, 
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f, 
        -0.5f, 0.5f, 0.5f
    };
};

struct AF_Pyramid{
    float verticies [27]={
        -0.5f, -0.5f, -0.5f, 
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f, 
        -0.5f, -0.5f, 0.5f,

        0.0f, 0.5f, 0.0f,

        -0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f, 0.5f,

        0.5f, -0.5f, -0.5f, 
        0.5f, -0.5f, 0.5f
    };
};

