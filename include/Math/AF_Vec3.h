#pragma once
#include <cmath>

struct AF_Vec3{

    float x;
    float y;
    float z;

    //Constructors
    AF_Vec3();
    AF_Vec3(float x, float y, float z);

    //Operators
    //Add Operator
    AF_Vec3 operator+(const AF_Vec3& other) const {
        return AF_Vec3(x + other.x, y + other.y, z + other.z);
    }

    //Subtract Operator
    AF_Vec3 operator-(const AF_Vec3& other) const {
        return AF_Vec3(x - other.x, y - other.y, z - other.z);
    }

    //Multiply Operator
    AF_Vec3 operator*(const AF_Vec3& other) const{
        return AF_Vec3(x * other.x, y * other.y, z * other.z);
    }

    //Dot Product
    float dot(const AF_Vec3& other) const{
        return x * other.x + y * other.y + z * other.z;
    }

    //Magnitude of vector
    float magnitude() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    //Normalize vector
    void normalize(){
        float mag = magnitude();
        x /= mag;
        y /= mag;
        z /= mag;
    }
};