#ifndef TORSO_H
#define TORSO_H

#include "Shapes/cube.h"

class Torso : public Cube
{
public:
    Torso();
protected:

    void drawShape();
};

#endif // TORSO_H
