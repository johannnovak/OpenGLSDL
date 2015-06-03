#include "EditableObject3D.h"


EditableObject3D::EditableObject3D()
{
}

EditableObject3D::~EditableObject3D()
{
}

void EditableObject3D::setComponents(GLfloat* _vertices, unsigned int _vertexCount, GLfloat* _normals, GLfloat* _uvs)
{
	this->m_vertices = _vertices;
	this->m_vertexCount = _vertexCount;
	this->m_normals = _normals;
	this->m_uvs = _uvs;
}

void EditableObject3D::setIndices(GLushort* _indices, unsigned int _indexCount)
{
	this->m_indices = _indices;
	this->m_indexCount = _indexCount;
}

//--------------------------------------------
bool EditableObject3D::defineNormals()
{
	return m_normals != nullptr;
}

//--------------------------------------------
bool EditableObject3D::defineUVs()
{
	return m_uvs != nullptr;
}

//--------------------------------------------
bool EditableObject3D::defineColors()
{
	return m_colors != nullptr;
}