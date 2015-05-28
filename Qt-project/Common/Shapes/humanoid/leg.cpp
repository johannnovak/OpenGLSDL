#include "leg.h"

Leg::Leg():Cube(1.0f,1.0f,5.0f,0.0f,0.0f,0.0f,0.3,0.3,0.3,0.3,0.3,0.3)
{
}

void Leg::drawShape()
{
    Cube::drawShape();
}
