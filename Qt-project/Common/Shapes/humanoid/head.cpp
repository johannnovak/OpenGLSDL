#include "head.h"

Head::Head():Cube(2.0f,2.0f,2.0f,0.0f,0.0f,0.0f,0.5f,0.5f,0.5f,0.5f,0.5f,0.5f)
{
}



void Head::drawShape()
{
    Cube::drawShape();
}
