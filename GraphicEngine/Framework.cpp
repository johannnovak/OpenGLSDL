#include "Framework.h"

using namespace std;

Framework::Framework()
{
}


Framework::~Framework()
{
}

bool Framework::createProgram(const char* _vShaderFile, const char* _fShaderFile, const char* _programName)
{
	GLint status, logSize;
	char* log;

	GLuint program = glCreateProgram();

	GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
	const char* vsStr = loadFile(_vShaderFile);
	glShaderSource(vshader, 1, &vsStr, NULL);
	glCompileShader(vshader);
	glGetShaderiv(vshader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		glGetShaderiv(vshader, GL_INFO_LOG_LENGTH, &logSize);
		log = new char[logSize + 1];
		glGetShaderInfoLog(vshader, logSize, &logSize, log);
		log[logSize] = '\0';
		LogManager::showError(("Error in vs: " + string(log)).c_str());
		delete[] log;
		log = NULL;
		return false;
	}
	glAttachShader(program, vshader);

	GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fsStr = loadFile("Shaders/shader.fs");
	glShaderSource(fshader, 1, &fsStr, NULL);
	glCompileShader(fshader);
	glGetShaderiv(fshader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		glGetShaderiv(fshader, GL_INFO_LOG_LENGTH, &logSize);
		log = new char[logSize + 1];
		glGetShaderInfoLog(fshader, logSize, &logSize, log);
		log[logSize] = '\0';
		LogManager::showError(("Error in fs: "+string(log)).c_str());
		delete[] log;
		log = NULL;
		return false;
	}
	glAttachShader(program, fshader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
		log = new char[logSize + 1];
		glGetProgramInfoLog(program, logSize, &logSize, log);
		log[logSize] = '\0';
		LogManager::showError(("Error in link: " + string(log)).c_str());
		delete[] log;
		log = NULL;
		return false;
	}

	delete[] vsStr;
	delete[] fsStr;

	m_programs.push_back(program);
	m_programNames.push_back(string(_programName));
	return true;
}

void Framework::activateProgram(const char* _programName)
{
	GLuint prog = getProgram(_programName);
	glUseProgram(prog);
	m_currentProgram = prog;
}

const char* Framework::loadFile(const char* _fileName)
{
	ifstream file(_fileName);
	string content;

	if (file.is_open())
	{
		file.seekg(0, std::ios::end);
		content.reserve(file.tellg());
		file.seekg(0, std::ios::beg);

		content.assign((std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>());

		file.close();
	}

	char* contentPtr = new char[content.size()+1];
	for (int i = 0; i < content.size(); ++i)
		contentPtr[i] = content[i];

	contentPtr[content.size()] = '\0';
	return contentPtr;
}

GLuint Framework::getProgram(const char* _programName)
{
	string pName(_programName);

	for (int i = 0; i < m_programNames.size(); ++i)
	{
		if (m_programNames[i] == pName)
		{
			return m_programs[i];
		}
	}

	return 0;
}

GLuint Framework::getCurrentProgram()
{
	return m_currentProgram;
}