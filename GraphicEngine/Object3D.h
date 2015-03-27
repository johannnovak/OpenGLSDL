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

	virtual float* getWorld() = 0;
	virtual GLuint getBuffer(BufferType _type) = 0;

};

