#ifndef __OBJECT3D_H__
#define __OBJECT3D_H__

#include "Types.h"

#include "GL/glew.h"

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

    protected:
        GLushort* m_indices;
        uint32  m_indexCount;

        GLfloat* m_vertices;
        uint32 m_vertexCount;

        GLfloat* m_normals;
        GLfloat* m_colors;
        GLfloat* m_uvs;
    public:
        Object3D();
        ~Object3D();

        GLushort* getIndices();
        uint32 getIndiceCount();

        GLfloat* getVertices();
        uint32 getVertexCount();

        GLfloat* getNormals();
        GLfloat* getUVs();
        GLfloat* getColors();

        void setColor(float32 r, float32 g, float32 b);

        virtual bool defineNormals();
        virtual bool defineUVs();
        virtual bool defineColors();

};

#endif // __OBJECT3D_H__
