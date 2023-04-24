#pragma once
#include "Math/AF_Math.h"
struct AF_Vertex {
    AF_Vec3 position;   //Position of vertex
    AF_Vec3 normal;     //Normal of vertex
    AF_Vec3 color;      //Color of vertex
    AF_Vec2 texCoord;   //Texture coordinate of vertex
    AF_Vec3 tangent;    //Tangent of vertex
    AF_Vec3 bitangent;  //Bitangent of vertex
};
