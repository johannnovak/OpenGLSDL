#ifndef VEC3_H
#define VEC3_H

#include "Types.h"

class Vec3
{
public:
    Vec3();
    Vec3(float32 _x, float32 _y, float32 _z);

    float32 m_x;
    float32 m_y;
    float32 m_z;
};

#endif // VEC3_H
