#ifndef QUATERNION_H
#define QUATERNION_H

#include "vec3.h"
#include <iostream>
#include <cmath>

class Quaternion
{
private:

public:
    Quaternion(float32 _w,float32 _x,float32 _y,float32 _z);

    Quaternion operator*(const Quaternion& _q) const;
    Vec3 operator*(const Vec3& _vec);
    Quaternion operator*(float32 _f) const;
    Quaternion operator+(const Quaternion& _q);
    Quaternion& operator*=(const Quaternion& _q);
    float32 dot(const Quaternion& _q) const;
    void set(float32 _x,float32 _y,float32 _z);
    void setFromAxis(float32 _angle, float32 _ax,float32 _ay,float32 _az);
    Quaternion conjugate();
    static Quaternion slerp(const Quaternion& _q0, const Quaternion& _q1, float32 _t);
    void normalize();
    void setRotationMatrix(float32* _mat);
    float32 norme();


    float32 m_w;
    float32 m_x;
    float32 m_y;
    float32 m_z;

    friend std::ostream& operator<<(std::ostream& _o, const Quaternion& _q);

};

#endif // QUATERNION_H
