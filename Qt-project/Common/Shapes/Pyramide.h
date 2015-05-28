#ifndef PYRAMIDE_H
#define PYRAMIDE_H

#include "Object3D.h"

class Pyramide : public Object3D
{
public:
    Pyramide(float n, float rayon, float height);

protected:
    void drawShape();
private :
    float nbSides;
    float rayon;
    float height;
};

#endif // PYRAMIDE_H
