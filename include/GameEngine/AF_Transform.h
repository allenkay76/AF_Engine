#pragma once
#include "Math/AF_Vec3.h"
#include "Math/AF_Quat.h"
struct AF_Transform {
    //Tranform components
    AF_Vec3 position;
    AF_Quat rotation;
    AF_Vec3 scale;
};

