#include "Cube.h"


Cube::Cube() : Object3D()
{
	float s = 0.5f;

	m_vertices = new GLfloat[72];
	m_vertexCount = 72;

	m_indices = new GLushort[36];
	m_indexCount = 36;

	m_normals = new GLfloat[72];
	m_colors = new GLfloat[72];

	float vertices[] = {
		-s, -s, s, // Front
		-s, s, s,
		s, -s, s,
		s, s, s,

		s, -s, s, // Right
		s, s, s,
		s, -s, -s,
		s, s, -s,

		s, -s, -s, // Back
		s, s, -s,
		-s, -s, -s,
		-s, s, -s,

		-s, -s, -s, // Left
		-s, s, -s,
		-s, -s, s,
		-s, s, s,

		-s, s, s, // Top
		-s, s, -s,
		s, s, s,
		s, s, -s,

		-s, -s, -s, // Bottom
		-s, -s, s,
		s, -s, -s,
		s, -s, s
	};

	float normals[] = {
		// FRONT
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,

		// RIGHT
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,

		// BACK
		0, 0, -1,
		0, 0, -1,
		0, 0, -1,
		0, 0, -1,

		// LEFT
		-1, 0, 0,
		-1, 0, 0,
		-1, 0, 0,
		-1, 0, 0,

		// TOP
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,

		// BOTTOM
		0, -1, 0,
		0, -1, 0,
		0, -1, 0,
		0, -1, 0,

	};

	GLfloat colors[] = {
		// FRONT
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,

		// RIGHT
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,

		// BACK
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,

		// LEFT
		1, 0, 1,
		1, 0, 1,
		1, 0, 1,
		1, 0, 1,

		// TOP
		0, 1, 1,
		0, 1, 1,
		0, 1, 1,
		0, 1, 1,

		// BOTTOM
		1, 1, 0,
		1, 1, 0,
		1, 1, 0,
		1, 1, 0,
	};

	unsigned short indices[] = {
		0, 1, 2, // Front
		1, 2, 3,

		4, 5, 6, // Right
		5, 6, 7,

		8, 9, 10, // Back
		9, 10, 11,

		12, 13, 14, // Left
		13, 14, 15,

		16, 17, 18, // Top
		17, 18, 19,

		20, 21, 22, // Bottom
		21, 22, 23,
	};

	for (unsigned int i = 0; i < m_vertexCount; ++i)
	{
		m_vertices[i] = vertices[i];
		m_normals[i] = normals[i];
		m_colors[i] = colors[i];
	}

	for (unsigned int i = 0; i < m_indexCount; ++i)
	{
		m_indices[i] = indices[i];
	}
}


Cube::~Cube()
{
	delete[] m_vertices;
	delete[] m_colors;
	delete[] m_normals;
	delete[] m_indices;
	delete[] m_uvs;
}

bool Cube::defineNormals()
{
	return true;
}
bool Cube::defineUVs()
{
	return false;
}
bool Cube::defineColors()
{
	return true;
}