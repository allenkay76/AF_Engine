#pragma once
#include "Math/AF_Vec3.h"
//#include "Math/AF_Quat.h"
struct AF_Transform {
    //Tranform components
    AF_Vec3 position { 0.0f, 0.0f, 0.0f };
    AF_Vec3 rotation { 0.0f, 0.0f, 0.0f };
    AF_Vec3 scale { 1.0f, 1.0f, 1.0f };
};

