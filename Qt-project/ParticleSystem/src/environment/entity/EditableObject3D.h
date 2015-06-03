#ifndef __EDITABLEOBJECT3D_H__
#define __EDITABLEOBJECT3D_H__

#include "Object3D.h"

class EditableObject3D : public Object3D
{
public:
    EditableObject3D();
    ~EditableObject3D();

public:
    void setComponents(GLfloat* _vertices, uint32 _vertexCount, GLfloat* _normals, GLfloat* _uvs);
    void setIndices(GLushort* _indices, uint32 _indexCount);

    bool defineNormals();
    bool defineUVs();
    bool defineColors();
};

#endif // __EDITABLEOBJECT3D_H__
