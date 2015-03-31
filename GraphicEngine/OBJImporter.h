#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Helpers.h"
#include "LogManager.h"
#include "Object3D.h"
#include "EditableObject3D.h"

struct ObjParserVertex
{
	float x;
	float y;
	float z;
};

struct ObjParserNormal
{
	float x;
	float y;
	float z;
};

struct ObjParserUv
{
	float u;
	float v;
	float w;
};

enum ObjParserFaceType
{
	ObjParserFaceType_POLYGON = 0,
	ObjParserFaceType_TRIANGLE
};

struct ObjParserFaceIndex
{
	unsigned short vertex;
	unsigned short normal;
	unsigned short uv;
};

struct ObjParserFace
{
	ObjParserFaceType type;

	ObjParserFaceIndex i1;
	ObjParserFaceIndex i2;
	ObjParserFaceIndex i3;
	ObjParserFaceIndex i4;
};

struct ObjParserObject
{
	ObjParserVertex* vertices;
	ObjParserNormal* normals;
	ObjParserUv* uvs;

	ObjParserFace* faces;

	unsigned int faceCount;
	unsigned int vertexCount;
	unsigned int normalCount;
	unsigned int uvCount;
};

class OBJImporter
{
public:
	OBJImporter();
	~OBJImporter();

public:
	static Object3D* importObject(const char* _file);

private:
	static ObjParserObject parseFile(std::ifstream& _file);
	static void parseFaceIndex(const std::string& _str, ObjParserFaceIndex& _index);
	static void copyParserObject(ObjParserObject& _src, ObjParserObject& _dest);
	static void deleteObjParserObject(ObjParserObject& _obj);
};

