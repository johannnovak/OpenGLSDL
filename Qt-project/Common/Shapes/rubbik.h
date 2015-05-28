#ifndef RUBBIK_H
#define RUBBIK_H

#include "Object3D.h"
#include "Shapes/cube.h"

class Rubbik : public Object3D
{
public:
    Rubbik(int _nb);

    void addAngle(int index, float da);

protected:
    void drawShape();

    int m_nb;
    int* angles;
    int indexToTurn;
    bool xTurning;
    bool yTurning;
    bool zTurning;

};

#endif // RUBBIK_H
