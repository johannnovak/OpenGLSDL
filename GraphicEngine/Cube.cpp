#include "Cube.h"


Cube::Cube() : m_world(1)
{
	m_buffers = new GLuint[3];

	glCreateBuffers(3, m_buffers);
	float s = 0.5f;
	float vertices[] = {
		-s, -s, s, // 0 FRONT LEFT DOWN
		-s, s, s,  // 1 FRONT LEFT UP
		s, s, s,   // 2 FRONT RIGHT UP
		s, -s, s,  // 3 FRONT RIGHT DOWN

		-s, -s, -s,// 4 BACK LEFT DOWN
		-s, s, -s, // 5 BACK LEFT UP
		s, s, -s,  // 6 BACK RIGHT UP
		s, -s, -s, // 7 BACK RIGHT DOWN
	};

	short indices[] = {
		0, 1, 2, // FRONT
		0, 2, 3,

		3, 2, 6, // RIGHT
		3, 6, 7,

		7, 6, 5, // BACK
		7, 5, 4,

		4, 5, 1, // LEFT
		4, 1, 0,

		1, 5, 6, // TOP
		1, 6, 2,

		4, 0, 3, // BACK
		4, 3, 7,
	};

}


Cube::~Cube()
{
}

float* Cube::getWorld()
{
	return &m_world[0][0];
}

GLuint Cube::getBuffer(BufferType _type)
{
	switch (_type)
	{
	case BufferType::COLOR_BUFFER:
		return m_buffers[2];

	case BufferType::INDEX_BUFFER:
		return m_buffers[1];

	case BufferType::VERTEX_BUFFER:
		return m_buffers[0];
	}

	return 0;
}
