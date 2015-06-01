#pragma once

#include <glm/glm.hpp>

#include "Object3D.h"

class Cube :
	public Object3D
{
public:
	Cube();
	~Cube();

public:
	bool defineNormals();
	bool defineUVs();
	bool defineColors();
};

