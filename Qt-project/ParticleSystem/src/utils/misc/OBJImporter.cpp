#include "OBJImporter.h"

OBJImporter::OBJImporter()
{
}


OBJImporter::~OBJImporter()
{
}

Object3D* OBJImporter::importObject(const char* _file)
{
    EditableObject3D* output = new EditableObject3D();

    ObjParserObject intermediate;
    std::ifstream file(_file);

    if (file.is_open())
    {
        intermediate = parseFile(file);

        GLushort* indices = new GLushort[65535];
        GLfloat* vertices = new GLfloat[intermediate.vertexCount * 3];
        GLfloat* normals = new GLfloat[intermediate.vertexCount * 3];
        int* normalRefCount = new int[intermediate.vertexCount];
        unsigned short normalIndex;

        for (unsigned int i = 0; i < intermediate.vertexCount; ++i)
        {
            normals[i * 3 + 0] = 0;
            normals[i * 3 + 1] = 0;
            normals[i * 3 + 2] = 0;

            normalRefCount[i] = 0;
        }

        unsigned int indexCount = 0;
        for (unsigned int i = 0; i < intermediate.faceCount; ++i)
        {
            if (intermediate.faces[i].type == ObjParserFaceType_POLYGON)
            {
                indices[indexCount++] = intermediate.faces[i].i1.vertex-1;
                indices[indexCount++] = intermediate.faces[i].i2.vertex-1;
                indices[indexCount++] = intermediate.faces[i].i3.vertex-1;

                indices[indexCount++] = intermediate.faces[i].i1.vertex - 1;
                indices[indexCount++] = intermediate.faces[i].i3.vertex - 1;
                indices[indexCount++] = intermediate.faces[i].i4.vertex - 1;

                if (intermediate.faces[i].i1.normal != 0)
                {
                    normalIndex = intermediate.faces[i].i1.normal - 1;
                    normals[normalIndex * 3 + 0] += intermediate.normals[normalIndex].x;
                    normals[normalIndex * 3 + 1] += intermediate.normals[normalIndex].y;
                    normals[normalIndex * 3 + 2] += intermediate.normals[normalIndex].z;
                    normalRefCount[normalIndex]++;
                }

                if (intermediate.faces[i].i2.normal != 0)
                {
                    normalIndex = intermediate.faces[i].i2.normal - 1;
                    normals[normalIndex * 3 + 0] += intermediate.normals[normalIndex].x;
                    normals[normalIndex * 3 + 1] += intermediate.normals[normalIndex].y;
                    normals[normalIndex * 3 + 2] += intermediate.normals[normalIndex].z;
                    normalRefCount[normalIndex]++;
                }

                if (intermediate.faces[i].i3.normal != 0)
                {
                    normalIndex = intermediate.faces[i].i3.normal - 1;
                    normals[normalIndex * 3 + 0] += intermediate.normals[normalIndex].x;
                    normals[normalIndex * 3 + 1] += intermediate.normals[normalIndex].y;
                    normals[normalIndex * 3 + 2] += intermediate.normals[normalIndex].z;
                    normalRefCount[normalIndex]++;
                }

                if (intermediate.faces[i].i4.normal != 0)
                {
                    normalIndex = intermediate.faces[i].i4.normal - 1;
                    normals[normalIndex * 3 + 0] += intermediate.normals[normalIndex].x;
                    normals[normalIndex * 3 + 1] += intermediate.normals[normalIndex].y;
                    normals[normalIndex * 3 + 2] += intermediate.normals[normalIndex].z;
                    normalRefCount[normalIndex]++;
                }
            }
            else
            {
                indices[indexCount++] = intermediate.faces[i].i1.vertex-1;
                indices[indexCount++] = intermediate.faces[i].i2.vertex-1;
                indices[indexCount++] = intermediate.faces[i].i3.vertex-1;

                if (intermediate.faces[i].i1.normal != 0)
                {
                    normalIndex = intermediate.faces[i].i1.normal - 1;
                    normals[normalIndex * 3 + 0] += intermediate.normals[normalIndex].x;
                    normals[normalIndex * 3 + 1] += intermediate.normals[normalIndex].y;
                    normals[normalIndex * 3 + 2] += intermediate.normals[normalIndex].z;
                    normalRefCount[normalIndex]++;
                }

                if (intermediate.faces[i].i2.normal != 0)
                {
                    normalIndex = intermediate.faces[i].i2.normal - 1;
                    normals[normalIndex * 3 + 0] += intermediate.normals[normalIndex].x;
                    normals[normalIndex * 3 + 1] += intermediate.normals[normalIndex].y;
                    normals[normalIndex * 3 + 2] += intermediate.normals[normalIndex].z;
                    normalRefCount[normalIndex]++;
                }

                if (intermediate.faces[i].i3.normal != 0)
                {
                    normalIndex = intermediate.faces[i].i3.normal - 1;
                    normals[normalIndex * 3 + 0] += intermediate.normals[normalIndex].x;
                    normals[normalIndex * 3 + 1] += intermediate.normals[normalIndex].y;
                    normals[normalIndex * 3 + 2] += intermediate.normals[normalIndex].z;
                    normalRefCount[normalIndex]++;
                }
            }
        }

        for (unsigned int i = 0; i < intermediate.vertexCount; ++i)
        {
            vertices[i * 3 + 0] = intermediate.vertices[i].x;
            vertices[i * 3 + 1] = intermediate.vertices[i].y;
            vertices[i * 3 + 2] = intermediate.vertices[i].z;

            normals[i * 3 + 0] /= (normalRefCount[i] > 0 ? normalRefCount[i] : 1);
            normals[i * 3 + 1] /= (normalRefCount[i] > 0 ? normalRefCount[i] : 1);
            normals[i * 3 + 2] /= (normalRefCount[i] > 0 ? normalRefCount[i] : 1);
        }

        GLushort* temp = indices;
        indices = nullptr;
        indices = new GLushort[indexCount];
        for (unsigned int i = 0; i < indexCount; ++i)
            indices[i] = temp[i];

        delete[] temp;
        delete[] normalRefCount;

        output->setComponents(vertices, intermediate.vertexCount, normals, nullptr);
        output->setIndices(indices, indexCount);

        deleteObjParserObject(intermediate);

        return output;
    }
    else
    {
        std::string message;
        message = "Unable to open file ";
        message += _file;
        LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_ERROR, message);

        return nullptr;
    }
}

void OBJImporter::deleteObjParserObject(ObjParserObject& _obj)
{
    delete _obj.faces;
    delete _obj.normals;
    delete _obj.uvs;
    delete _obj.vertices;
}

void OBJImporter::copyParserObject(ObjParserObject& _src, ObjParserObject& _dest)
{
    _dest.faces = new ObjParserFace[_src.faceCount];
    _dest.normals = new ObjParserNormal[_src.normalCount];
    _dest.vertices = new ObjParserVertex[_src.vertexCount];
    _dest.uvs = new ObjParserUv[_src.uvCount];

    for (unsigned int i = 0; i < _src.faceCount; ++i)
    {
        _dest.faces[i] = _src.faces[i];
    }
    for (unsigned int i = 0; i < _src.normalCount; ++i)
    {
        _dest.normals[i] = _src.normals[i];
    }
    for (unsigned int i = 0; i < _src.vertexCount; ++i)
    {
        _dest.vertices[i] = _src.vertices[i];
    }
    for (unsigned int i = 0; i < _src.uvCount; ++i)
    {
        _dest.uvs[i] = _src.uvs[i];
    }

    _dest.faceCount = _src.faceCount;
    _dest.normalCount = _src.normalCount;
    _dest.vertexCount = _src.vertexCount;
    _dest.uvCount = _src.uvCount;
}

void OBJImporter::parseFaceIndex(const std::string& _str, ObjParserFaceIndex& _index)
{
    std::vector<std::string>* components = Helpers::splitString(_str.c_str(), '/', true);
    unsigned int componentSize = components->size();
    unsigned short iv=0, it=0, in=0;

    if (componentSize == 1) // Only vertex
    {
        sscanf(components->at(0).c_str(), "%hu", &iv);
        _index.vertex = iv;
        _index.normal = 0;
        _index.uv = 0;
    }

    if (componentSize == 2) // vertex and texture
    {
        sscanf(components->at(0).c_str(), "%hu", &iv);
        sscanf(components->at(1).c_str(), "%hu", &it);
        _index.vertex = iv;
        _index.normal = 0;
        _index.uv = it;
    }

    if (componentSize == 3) // vertex, texture and normal
    {
        sscanf(components->at(0).c_str(), "%hu", &iv);
        if (components->at(1) != "")
            sscanf(components->at(1).c_str(), "%hu", &it);
        sscanf(components->at(2).c_str(), "%hu", &in);
        _index.vertex = iv;
        _index.normal = in;
        _index.uv = it;
    }

    delete components;
}

ObjParserObject OBJImporter::parseFile(std::ifstream& _file)
{
    const int bufferSize = 0x10000;
    unsigned int vertexCount = 0, normalCount = 0, textureCount = 0, faceCount = 0;

    ObjParserObject output;

    // First lets over assign the output
    output.faces = new ObjParserFace[bufferSize];
    output.normals = new ObjParserNormal[bufferSize];
    output.uvs = new ObjParserUv[bufferSize];
    output.vertices = new ObjParserVertex[bufferSize];
    output.faceCount = 0;

    // loop on the file line by line
    while (!_file.eof())
    {
        std::string line;
        float x, y, z;

        std::getline(_file, line);

        // passing on comments
        if (line[0] == '#' || line.empty())
            continue;

        // retreiving a vertex, a normal, a uv or a face
        if (sscanf(line.c_str(), "v  %f %f %f", &x, &y, &z) == 3) // vertex
        {
            output.vertices[vertexCount].x = x;
            output.vertices[vertexCount].y = y;
            output.vertices[vertexCount].z = z;
            vertexCount++;
        }
        else if (sscanf(line.c_str(), "vn %f %f %f", &x, &y, &z) == 3) // normal
        {
            output.normals[normalCount].x = x;
            output.normals[normalCount].y = y;
            output.normals[normalCount].z = z;
            normalCount++;
        }
        else if (sscanf(line.c_str(), "vt %f %f %f", &x, &y, &z) >= 2) // texture
        {
            output.uvs[textureCount].u = x;
            output.uvs[textureCount].v = y;
            output.uvs[textureCount].w = z;

            textureCount++;
        }
        else if (line[0] == 'f') // face
        {
            std::vector<std::string>* split = Helpers::splitString(line.c_str(), ' ', false);

            parseFaceIndex(split->at(1), output.faces[faceCount].i1);
            parseFaceIndex(split->at(2), output.faces[faceCount].i2);
            parseFaceIndex(split->at(3), output.faces[faceCount].i3);

            if (split->size() == 5)
            {
                parseFaceIndex(split->at(4), output.faces[faceCount].i4);
                output.faces[faceCount].type = ObjParserFaceType_POLYGON;
            }
            else
            {
                output.faces[faceCount].i4.normal = 0;
                output.faces[faceCount].i4.uv = 0;
                output.faces[faceCount].i4.vertex= 0;
                output.faces[faceCount].type = ObjParserFaceType_TRIANGLE;
            }

            delete split;
            faceCount++;
        }
        else  // not recognised (maybe log or not i don't know)
        {

        }
    }

    // adjust output buffers

    ObjParserObject temp;
    temp.faces = output.faces;
    temp.normals = output.normals;
    temp.uvs = output.uvs;
    temp.vertices = output.vertices;
    temp.faceCount = faceCount;
    temp.normalCount = normalCount;
    temp.vertexCount = vertexCount;
    temp.uvCount = textureCount;

    copyParserObject(temp, output);
    delete[] temp.faces;
    delete[] temp.normals;
    delete[] temp.uvs;
    delete[] temp.vertices;

    return output;
}
