#pragma once

#include <unordered_map>
#include <string>
#include <GL\glew.h>

#include "Helpers.h"

class Shader
{
public:
	Shader(const char* _shaderName);
	virtual ~Shader();

	void activate();

	std::string& getName();
	GLuint getProgram();
	GLuint getUniformLocation(const char* _name);
	GLuint getAttrLocation(const char* _name);

	bool registerUniform(const char* _name);
	bool registerAttribute(const char* _name);

	bool transmitUniformMat4(const char* _name, const GLfloat* _mat, GLboolean _transpose = GL_TRUE);
	bool transmitUniformVect3(const char* _name, const GLfloat* _vect);
	bool transmitUniformVect4(const char* _name, const GLfloat* _vect);

	bool transmitUniformInt(const char* _name, const GLint _int);

	bool transmitAttrMat4(const char* _name, const GLfloat* _mat);
	bool transmitAttrVect3(const char* _name, const GLfloat* _vect);
	bool transmitAttrVect4(const char* _name, const GLfloat* _vect);

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

public:
	static void activate(Shader* _shader);
	static Shader* s_activeShader;
};

