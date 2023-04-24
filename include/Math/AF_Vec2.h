#pragma once
#include <cmath>

struct AF_Vec2{

    float x;
    float y;

    //Constructors
    AF_Vec2();
    AF_Vec2(float x, float y);

    //Operators
    //Add Operator
    AF_Vec2 operator+(const AF_Vec2& other) const {
        return AF_Vec2(x + other.x, y + other.y);
    }

    //Subtract Operator
    AF_Vec2 operator-(const AF_Vec2& other) const {
        return AF_Vec2(x - other.x, y - other.y);
    }

    //Multiply Operator
    AF_Vec2 operator*(const AF_Vec2& other) const{
        return AF_Vec2(x * other.x, y * other.y);
    }

    //Dot Product
    float dot(const AF_Vec2& other) const{
        return x * other.x + y * other.y;
    }

    //Magnitude of vector
    float magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    //Normalize vector
    void normalize(){
        float mag = magnitude();
        x /= mag;
        y /= mag;
    }

};