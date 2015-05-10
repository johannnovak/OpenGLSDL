#include "Plane.h"


Plane::Plane(float _x1, float _z1, float _x2, float _z2, float _y)
{
	m_vertices = new GLfloat[12];
	m_colors = new GLfloat[12];
	m_vertexCount = 4;

	m_indices = new GLushort[6];
	m_indexCount = 6;

	m_vertices[0]	= _x1;
	m_vertices[1]	= _y;
	m_vertices[2]	= _z1;

	m_vertices[3]	= _x2;
	m_vertices[4]	= _y;
	m_vertices[5]	= _z1;

	m_vertices[6]	= _x1;
	m_vertices[7]	= _y;
	m_vertices[8]	= _z2;

	m_vertices[9]	= _x2;
	m_vertices[10]	= _y;
	m_vertices[11]	= _z2;

	m_colors[0] = 0.494;
	m_colors[1] = 0.494;
	m_colors[2] = 0.494;
	m_colors[3] = 0.494;
	m_colors[4] = 0.494;
	m_colors[5] = 0.494;
	m_colors[6] = 0.494;
	m_colors[7] = 0.494;
	m_colors[8] = 0.494;
	m_colors[9] = 0.494;
	m_colors[10] = 0.494;
	m_colors[11] = 0.494;

	m_indices[0] = 0;
	m_indices[1] = 1;
	m_indices[2] = 2;

	m_indices[3] = 2;
	m_indices[4] = 1;
	m_indices[5] = 3;
}


Plane::~Plane()
{
}

bool Plane::defineColors()
{
	return true;
}