#ifndef __CUBE_H__
#define __CUBE_H__

#include "Object3D.h"

#include <glm/glm.hpp>

class Cube : public Object3D
{
public:
    Cube();
    ~Cube();

public:
    bool defineNormals();
    bool defineUVs();
    bool defineColors();
};

#endif // __CUBE_H__
