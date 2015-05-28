#ifndef CUBE_H
#define CUBE_H

#include "Object3D.h"

class Cube : public Object3D
{
    public:
        Cube(float _width, float _height, float _depth, float _x, float _y, float _z, float _colorUp, float  _colorDown, float _colorRight, float _colorLeft,float _colorFront, float _colorBack);
    protected:
        void drawShape();
        float m_width;
        float m_height;
        float m_depth;
        float m_x;
        float m_y;
        float m_z;
        float m_colorUp;
        float m_colorDown;
        float m_colorRight;
        float  m_colorLeft;
        float m_colorFront;
        float  m_colorBack;
};

#endif // CUBE_H
