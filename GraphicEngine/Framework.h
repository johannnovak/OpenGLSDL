#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>

#include "LogManager.h"

class Framework
{
public:
	Framework();
	virtual ~Framework();

	bool createProgram(const char* _vShaderFile, const char* _fShaderFile, const char* _programName);
	void activateProgram(const char* _programName);

	GLuint getProgram(const char* _programName);
	GLuint getCurrentProgram();

private:
	const char* loadFile(const char* _fileName);

private:
	std::vector<std::string> m_programNames;
	std::vector<GLuint> m_programs;

	GLint m_currentProgram;
};

