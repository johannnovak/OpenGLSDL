#pragma once

#include <unordered_map>
#include <string>
#include <sstream>
#include "GL/glew.h"

#include "Helpers.h"

enum ShaderAttributeType
{
	ShaderAttributeType_POSITION = 0,
	ShaderAttributeType_COLOR,
	ShaderAttributeType_NORMAL,
	ShaderAttributeType_UV,

	ShaderAttributeType_LAST,
};

enum ShaderUniformType
{
	ShaderUniformType_WORLD = 0,
	ShaderUniformType_VIEW,
	ShaderUniformType_PROJECTION,

	ShaderUniformType_LAST,
};

class Shader
{
public:
	Shader();
	Shader(const char* _shaderName);
	virtual ~Shader();

	bool load(const char* _shaderName);

	void activate();

	std::string& getName();
	GLuint getProgram();

	GLuint getUniformLocation(const char* _name);
	GLuint getUniformLocation(ShaderUniformType _type);

	GLuint getAttrLocation(const char* _name);
	GLuint getAttrLocation(ShaderAttributeType _type);

	bool registerUniform(const char* _name);
	bool registerUniform(const char* _name, ShaderUniformType _type);

	bool registerAttribute(const char* _name);
	bool registerAttribute(const char* _name, ShaderAttributeType _type);

	bool transmitUniformMat4(const char* _name, const GLfloat* _mat, GLboolean _transpose = GL_TRUE);
	bool transmitUniformMat4(ShaderUniformType _type, const GLfloat* _mat, GLboolean _transpose = GL_TRUE);

	bool transmitUniformVect3(const char* _name, const GLfloat* _vect);
	bool transmitUniformVect4(const char* _name, const GLfloat* _vect);

	bool transmitUniformInt(const char* _name, const GLint _int);
	bool transmitUniformFloat(const char* _name, const GLint _float);

	bool transmitAttrMat4(const char* _name, const GLfloat* _mat);
	bool transmitAttrMat4(ShaderAttributeType _type, const GLfloat* _mat);

	bool transmitAttrVect3(const char* _name, const GLfloat* _vect);
	bool transmitAttrVect3(ShaderAttributeType _type, const GLfloat* _vect);

	bool transmitAttrVect4(const char* _name, const GLfloat* _vect);
	bool transmitAttrVect4(ShaderAttributeType _type, const GLfloat* _vect);

	bool transmitAttrFloat(const char* _name, const GLfloat* _float);

	void enableAllAttrib();
	void disableAllAttrib();

private:
	void activateInternal();

	bool checkShaderError(GLuint _id, GLuint _type);
	bool checkProgramError(GLuint _id, GLuint _type);

private:
	std::string m_name;
	GLuint m_id;

	std::unordered_map<std::string, GLuint> m_attributes;
	std::unordered_map<std::string, GLuint> m_uniforms;

	GLuint m_attributeTypes[ShaderAttributeType_LAST];
	GLuint m_uniformTypes[ShaderUniformType_LAST];

public:
	static void activate(Shader* _shader);
	static Shader* s_activeShader;
};

