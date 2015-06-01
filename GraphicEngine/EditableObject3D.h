#pragma once

#include "Object3D.h"

class EditableObject3D : public Object3D
{
public:
	EditableObject3D();
	~EditableObject3D();

public:
	void setComponents(GLfloat* _vertices, unsigned int _vertexCount, GLfloat* _normals, GLfloat* _uvs);
	void setIndices(GLushort* _indices, unsigned int _indexCount);

	bool defineNormals();
	bool defineUVs();
	bool defineColors();
};

