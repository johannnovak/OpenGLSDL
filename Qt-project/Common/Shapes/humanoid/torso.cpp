#include "torso.h"

Torso::Torso():Cube(2.0f,3.0f,5.0f,0.0f,0.0f,0.0f,0.9f,0.9f,0.9f,0.9f,0.9f,0.9f)
{
}


void Torso::drawShape()
{
    Cube::drawShape();
}
