#pragma once
#include "Math/AF_Math.h"
struct AF_Mat4 {
    AF_Vec4 columns[4];

    // Constructors
    AF_Mat4() : columns{AF_Vec4(1.0f, 0.0f, 0.0f, 0.0f), AF_Vec4(0.0f, 1.0f, 0.0f, 0.0f), AF_Vec4(0.0f, 0.0f, 1.0f, 0.0f), AF_Vec4(0.0f, 0.0f, 0.0f, 1.0f)} {};

    // Accessors
    AF_Vec4& operator[](int index) { return columns[index]; }
    const AF_Vec4& operator[](int index) const { return columns[index]; }

    // Get pointer to the underlying data
    const float* data() const { return &columns[0].x; }
    float* data() { return &columns[0].x; }


    // Matrix multiplication
    AF_Mat4 operator*(const AF_Mat4& other) const {
        AF_Mat4 result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                float sum = 0.0f;
                for (int k = 0; k < 4; k++) {
                    sum += columns[k][j] * other[i][k];
                }
                result[i][j] = sum;
            }
        }
        return result;
    }

    // Static factory functions for common transformations
    static AF_Mat4 identity() { return AF_Mat4(); }
    static AF_Mat4 translate(const AF_Vec3& translation) {
        AF_Mat4 result;
        result[3] = AF_Vec4(translation.x, translation.y, translation.z, 1.0f);
        return result;
    }
    static AF_Mat4 rotate(float angle, const AF_Vec3& axis) {
        AF_Mat4 result;

        float radians = angle * (3.14159265358979323846f / 180.0f);
        float c = std::cos(radians);
        float s = std::sin(radians);
        float oneMinusC = 1.0f - c;

        float x = axis.x;
        float y = axis.y;
        float z = axis.z;

        result[0][0] = x * x * oneMinusC + c;
        result[0][1] = y * x * oneMinusC + z * s;
        result[0][2] = x * z * oneMinusC - y * s;

        result[1][0] = x * y * oneMinusC - z * s;
        result[1][1] = y * y * oneMinusC + c;
        result[1][2] = y * z * oneMinusC + x * s;

        result[2][0] = x * z * oneMinusC + y * s;
        result[2][1] = y * z * oneMinusC - x * s;
        result[2][2] = z * z * oneMinusC + c;

        result[3][3] = 1.0f;

        return result;
    }

    static AF_Mat4 scale(const AF_Vec3& scale) {
        AF_Mat4 result;
        result[0][0] = scale.x;
        result[1][1] = scale.y;
        result[2][2] = scale.z;
        return result;
    }
};
