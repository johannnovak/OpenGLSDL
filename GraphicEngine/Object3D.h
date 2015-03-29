#pragma once

#include <GL/glew.h>

enum BufferType
{
	VERTEX_BUFFER = 0,
	INDEX_BUFFER = 1,
	COLOR_BUFFER = 2,
	NORMAL_BUFFER = 3,
	TEXTURE_BUFFER = 4,

	LAST_BUFFER = 5
};

class Object3D
{
public:
	Object3D();
	~Object3D();

	GLushort* getIndices();
	unsigned int getIndiceCount();

	GLfloat* getVertices();
	unsigned int getVertexCount();

	GLfloat* getNormals();
	GLfloat* getUVs();
	GLfloat* getColors();

	virtual bool defineNormals();
	virtual bool defineUVs();
	virtual bool defineColors();

protected:
	GLushort* m_indices;
	unsigned int m_indexCount;

	GLfloat* m_vertices;
	unsigned int m_vertexCount;

	GLfloat* m_normals;
	GLfloat* m_uvs;
	GLfloat* m_colors;

};

