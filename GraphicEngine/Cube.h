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
	float* getWorld();
	GLuint getBuffer(BufferType _type);

private:
	glm::mat4 m_world;

	GLuint* m_buffers;
};

