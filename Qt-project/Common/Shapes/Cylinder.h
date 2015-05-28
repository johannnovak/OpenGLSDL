#ifndef CYLINDER_H
#define CYLINDER_H

#include "Object3D.h"

class Cylinder : public Object3D
{
public:
    Cylinder(float rayon, float height, float _x, float _y, float _z, float _colorUp, float  _colorDown);

protected:
        void drawShape();

private:
    float rayon;
    float height;
    float m_x;
    float m_y;
    float m_z;
    float m_colorUp;
    float m_colorDown;
};

#endif // CYLINDER_H
