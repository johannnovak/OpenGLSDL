#include "Object3D.h"

Object3D::Object3D() : m_indices(nullptr), m_indexCount(0), m_vertices(nullptr), m_vertexCount(0), m_normals(nullptr), m_colors(nullptr), m_uvs(nullptr)
{
}

Object3D::~Object3D()
{
	delete[] m_colors;
	delete[] m_indices;
	delete[] m_uvs;
	delete[] m_normals;
	delete[] m_vertices;
}

GLushort* Object3D::getIndices()
{
	return m_indices;
}

unsigned int Object3D::getIndiceCount()
{
	return m_indexCount;
}

GLfloat* Object3D::getVertices()
{
	return m_vertices;
}

unsigned int Object3D::getVertexCount()
{
	return m_vertexCount;
}

GLfloat* Object3D::getNormals()
{
	return m_normals;
}

GLfloat* Object3D::getUVs()
{
	return m_uvs;
}

GLfloat* Object3D::getColors()
{
	return m_colors;
}

bool Object3D::defineNormals()
{
	return false;
}

bool Object3D::defineUVs()
{
	return false;
}

bool Object3D::defineColors()
{
	return false;
}

void Object3D::setColor(float r, float g, float b)
{
	if (m_colors != nullptr)
		delete[] m_colors;

	m_colors = new GLfloat[m_vertexCount*3];
	for (unsigned int i = 0; i < m_vertexCount; ++i)
	{
		m_colors[i * 3 + 0] = r;
		m_colors[i * 3 + 1] = g;
		m_colors[i * 3 + 2] = b;	
	}
}