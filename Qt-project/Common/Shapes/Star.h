#ifndef STAR_H
#define STAR_H

#include "Object3D.h"

class Star : public Object3D
{
public:
    Star(float nbBranch, float width, float innerRadius,float outerRadius);

protected:
    void drawShape();
    float nbBranch;
    float width;
    float innerRadius;
    float outerRadius;

};

#endif // STAR_H
