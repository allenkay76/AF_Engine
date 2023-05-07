#pragma once
#include <cassert>

#include <cmath>

struct AF_Vec4{

    float x;
    float y;
    float z;
    float w;

    //Constructors
    AF_Vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {};
    AF_Vec4(float argX, float argY, float argZ, float argW) : x(argX), y(argY), z(argZ), w(argW) {};

    // [] Operators
    // Operator []
    float& operator[](int index) {
        assert(index >= 0 && index < 4);
        if (index == 0) return x;
        else if (index == 1) return y;
        else if (index == 2) return z;
        else return w;
    }

    const float& operator[](int index) const {
        assert(index >= 0 && index < 4);
        if (index == 0) return x;
        else if (index == 1) return y;
        else if (index == 2) return z;
        else return w;
    }

    //Add Operator
    AF_Vec4 operator+(const AF_Vec4& other) const {
        return AF_Vec4(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    //Subtract Operator
    AF_Vec4 operator-(const AF_Vec4& other) const {
        return AF_Vec4(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    //Multiply Operator
    AF_Vec4 operator*(const AF_Vec4& other) const{
        return AF_Vec4(x * other.x, y * other.y, z * other.z,  w * other.w);
    }

    //Dot Product
    float dot(const AF_Vec4& other) const{
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    //Magnitude of vector
    float magnitude() const {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }

    //Normalize vector
    void normalize(){
        float mag = magnitude();
        x /= mag;
        y /= mag;
        z /= mag;
        w /= mag;
    }
};