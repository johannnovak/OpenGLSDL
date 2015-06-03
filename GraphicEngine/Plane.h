#pragma once

#include "Object3D.h"

class Plane : public Object3D
{
public:
	Plane(float _x1, float _z1, float _x2, float _z2, float _y);
	~Plane();

	virtual bool defineColors();
};

