#include "Shader.h"

Shader* Shader::s_activeShader = nullptr;

using namespace std;

//------------------------------------------------
Shader::Shader() : m_name(), m_attributes(), m_uniforms()
{}

//------------------------------------------------
Shader::Shader(const char* _shaderName) : m_name(), m_attributes(), m_uniforms()
{
	load(_shaderName);
}

//------------------------------------------------
Shader::~Shader()
{
	glDeleteProgram(m_id);
}

//------------------------------------------------
bool Shader::load(const char* _shaderName)
{
    std::cout << "Loading shader " << _shaderName << std::endl;
	for (unsigned int i = 0; i < ShaderAttributeType_LAST; ++i)
		m_attributeTypes[i] = -1;

	for (unsigned int i = 0; i < ShaderUniformType_LAST; ++i)
		m_uniformTypes[i] = -1;

	m_name = string(_shaderName);

	string vsFile = m_name + ".vs";
	string fsFile = m_name + ".fs";

	string vsStr, fsStr;
	const char* vsPtr, *fsPtr;

	Helpers::loadFile(vsFile.c_str(), vsStr);
	Helpers::loadFile(fsFile.c_str(), fsStr);

	vsPtr = vsStr.c_str();
	fsPtr = fsStr.c_str();

	m_id = glCreateProgram();

	GLuint vsId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fsId = glCreateShader(GL_FRAGMENT_SHADER);

	// Compiling Vertex Shader
	glShaderSource(vsId, 1, &vsPtr, NULL);
	glCompileShader(vsId);

	// Log any error
	if (!checkShaderError(vsId, GL_COMPILE_STATUS))
	{
		glDeleteProgram(m_id);
		glDeleteShader(vsId);
		glDeleteShader(fsId);

		return false;
	}

	// Compiling Fragment Shader
	glShaderSource(fsId, 1, &fsPtr, NULL);
	glCompileShader(fsId);

	// Log any error
	if (!checkShaderError(fsId, GL_COMPILE_STATUS))
	{
		glDeleteProgram(m_id);
		glDeleteShader(vsId);
		glDeleteShader(fsId);

		return false;
	}

	// Attaching Shaders
	glAttachShader(m_id, vsId);
	glAttachShader(m_id, fsId);

	// Linking program
	glLinkProgram(m_id);

	// Log any error
	if (!checkProgramError(m_id, GL_LINK_STATUS))
	{
		glDeleteProgram(m_id);
		glDeleteShader(vsId);
		glDeleteShader(fsId);

		return false;
	}

	vsPtr = nullptr;
	fsPtr = nullptr;

    std::cout << "Shader loaded !" << std::endl;

	return true;
}

//------------------------------------------------
bool Shader::checkShaderError(GLuint _id, GLuint _type)
{
	GLint status, logSize;
	char* log = NULL;

	glGetShaderiv(_id, _type, &status);
	if (status != GL_TRUE)
	{
        glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &logSize);
		log = new char[logSize + 1];
		glGetShaderInfoLog(_id, logSize, &logSize, log);
		log[logSize] = '\0';
        LogManager::pushEvent(new LogEvent(LogEventType::AllLogEvent,LogLevel::ERROR, std::string("Error in vs: " + string(log))));
		delete[] log;
		log = NULL;
		return false;
	}

	return true;
}

//------------------------------------------------
bool Shader::checkProgramError(GLuint _id, GLuint _type)
{
	GLint status, logSize;
	char* log = NULL;

	glGetProgramiv(_id, _type, &status);
	if (status != GL_TRUE)
	{
		glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &logSize);
		log = new char[logSize + 1];
		glGetProgramInfoLog(_id, logSize, &logSize, log);
		log[logSize] = '\0';
        LogManager::pushEvent(new LogEvent(LogEventType::AllLogEvent, LogLevel::ERROR, std::string("Error in vs: " + string(log))));
		delete[] log;
		log = NULL;
		return false;
	}

	return true;
}

//------------------------------------------------
void Shader::activate()
{
	Shader::activate(this);
}

//------------------------------------------------
void Shader::activateInternal()
{
	glUseProgram(m_id);
}

//------------------------------------------------
string& Shader::getName()
{
	return m_name;
}

//------------------------------------------------
GLuint Shader::getProgram()
{
	return m_id;
}

//------------------------------------------------
GLuint Shader::getUniformLocation(const char* _name)
{
	string name(_name);

	if (m_uniforms.find(name) == m_uniforms.end())
	{
        LogManager::pushEvent(new LogEvent(LogEventType::AllLogEvent, LogLevel::ERROR, std::string(name + " attribute is not registered for shader " + m_name)));
        return -1;
	}

	return m_uniforms[name];
}

//------------------------------------------------
GLuint Shader::getUniformLocation(ShaderUniformType _type)
{
	if (_type != ShaderUniformType_LAST)
	{
		return m_uniformTypes[_type];
	}

	return -1;
}

//------------------------------------------------
GLuint Shader::getAttrLocation(const char* _name)
{
	string name(_name);

	if (m_attributes.find(name) == m_attributes.end())
	{
        LogManager::pushEvent(new LogEvent(LogEventType::AllLogEvent, LogLevel::ERROR, std::string(name + " attribute is not registered for shader " + m_name)));
		return -1;
	}

	return m_attributes[name];
}

//------------------------------------------------
GLuint Shader::getAttrLocation(ShaderAttributeType _type)
{
	if (_type != ShaderAttributeType_LAST)
	{
		return m_attributeTypes[_type];
	}

	return -1;
}

//------------------------------------------------
bool Shader::registerUniform(const char* _name)
{
	string name(_name);

	if (m_uniforms.find(name) != m_uniforms.end())
	{
		// LogManager::showError((name + " uniform is already registered for shader " + m_name).c_str());
		return false;
	}

	GLuint id = glGetUniformLocation(m_id, name.c_str());
	if (id == -1)
	{
        LogManager::pushEvent(new LogEvent(LogEventType::AllLogEvent, LogLevel::ERROR, std::string(name + " uniform does not exist in shader " + m_name)));
		return false;
	}

	m_uniforms[name] = id;
	return true;
}

//------------------------------------------------
bool Shader::registerUniform(const char* _name, ShaderUniformType _type)
{
	bool success = registerUniform(_name);
	if (success)
	{
		m_uniformTypes[_type] = getUniformLocation(_name);
	}

	return success;
}

//------------------------------------------------
bool Shader::registerAttribute(const char* _name)
{
	string name(_name);

	if (m_attributes.find(name) != m_attributes.end())
	{
		// LogManager::showError((name + " attribute is already registered for shader " + m_name).c_str());
		return false;
	}

	GLuint id = glGetAttribLocation(m_id, name.c_str());
	if (id == -1)
	{
        LogManager::pushEvent(new LogEvent(LogEventType::AllLogEvent, LogLevel::ERROR, name + " uniform does not exist in shader " + m_name));
		return false;
	}

	m_attributes[name] = id;
	return true;
}

//------------------------------------------------
bool Shader::registerAttribute(const char* _name, ShaderAttributeType _type)
{
	bool registered = registerAttribute(_name);
	if (registered == true)
	{
		m_attributeTypes[_type] = getAttrLocation(_name);
		return true;
	}
		
	return false;
}

//------------------------------------------------
bool Shader::transmitUniformMat4(const char* _name, const GLfloat* _mat, GLboolean _transpose)
{
	string name(_name);

	if (m_uniforms.find(name) == m_uniforms.end())
	{
        LogManager::pushEvent(new LogEvent(LogEventType::AllLogEvent, LogLevel::ERROR, name + " uniform is not registered for shader " + m_name));
		return false;
	}

	glUniformMatrix4fv(m_uniforms[name], 1, _transpose, _mat);

	return true;
}

//------------------------------------------------
bool Shader::transmitUniformMat4(ShaderUniformType _type, const GLfloat* _mat, GLboolean _transpose)
{
	if (m_uniformTypes[_type] == -1)
	{
		stringstream strstr;
		strstr << "Uniform type " << _type << " is not registered for shader " << m_name;
        LogManager::pushEvent(new LogEvent(LogEventType::AllLogEvent,LogLevel::ERROR, strstr.str()));

		return false;
	}

	glUniformMatrix4fv(m_uniformTypes[_type], 1, _transpose, _mat);

	return true;
}

//------------------------------------------------
bool Shader::transmitUniformVect3(const char* _name, const GLfloat* _vect)
{
	string name(_name);

	if (m_uniforms.find(name) == m_uniforms.end())
	{
        LogManager::pushEvent(new LogEvent(LogEventType::AllLogEvent, LogLevel::ERROR, name + " uniform is not registered for shader " + m_name));
        return false;
	}

	glUniform3fv(m_uniforms[name], 1, _vect);
	return true;
}

//------------------------------------------------
bool Shader::transmitUniformVect4(const char* _name, const GLfloat* _vect)
{
	string name(_name);

	if (m_uniforms.find(name) == m_uniforms.end())
	{
        LogManager::pushEvent(new LogEvent(LogEventType::AllLogEvent, LogLevel::ERROR, name + " uniform is not registered for shader " + m_name));
        return false;
	}

	glUniform4fv(m_uniforms[name], 1, _vect);
	return true;
}

//------------------------------------------------
bool Shader::transmitUniformInt(const char* _name, const GLint _int)
{
	string name(_name);

	if (m_uniforms.find(name) == m_uniforms.end())
	{
        LogManager::pushEvent(new LogEvent(LogEventType::AllLogEvent, LogLevel::ERROR, name + " uniform is not registered for shader " + m_name));
        return false;
	}

	glUniform1i(m_uniforms[name], _int);
	return true;
}

//------------------------------------------------
bool Shader::transmitUniformFloat(const char* _name, const GLint _float)
{
	string name(_name);

	if (m_uniforms.find(name) == m_uniforms.end())
	{
        LogManager::pushEvent(new LogEvent(LogEventType::AllLogEvent, LogLevel::ERROR, name + " uniform is not registered for shader " + m_name));
        return false;
	}

	glUniform1f(m_uniforms[name], _float);
	return true;
}

//------------------------------------------------
bool Shader::transmitAttrMat4(const char* _name, const GLfloat* _mat)
{
    LogManager::pushEvent(new LogEvent(LogEventType::AllLogEvent, LogLevel::ERROR, "transmitAttrMat4 is not implemented yet..."));
    return false;
}

//------------------------------------------------
bool Shader::transmitAttrVect3(const char* _name, const GLfloat* _vect)
{
	string name(_name);

	if (m_attributes.find(name) == m_attributes.end())
	{
        LogManager::pushEvent(new LogEvent(LogEventType::AllLogEvent,LogLevel::ERROR, name + " uniform is not registered for shader " + m_name));
        return false;
	}

	glVertexAttribPointer(m_attributes[name], 3, GL_FLOAT, GL_FALSE, 0, _vect);
	return true;
}

//------------------------------------------------
bool Shader::transmitAttrVect4(const char* _name, const GLfloat* _vect)
{
	string name(_name);

	if (m_attributes.find(name) == m_attributes.end())
	{
        LogManager::pushEvent(new LogEvent(LogEventType::AllLogEvent,LogLevel::ERROR, name + " uniform is not registered for shader " + m_name));
        return false;
	}

	glVertexAttribPointer(m_attributes[name], 4, GL_FLOAT, GL_FALSE, 0, _vect);
	return true;
}

//------------------------------------------------
bool Shader::transmitAttrMat4(ShaderAttributeType _type, const GLfloat* _mat)
{
    LogManager::pushEvent(new LogEvent(LogEventType::AllLogEvent,LogLevel::ERROR, "transmitAttrMat4 is not implemented yet..."));
    return false;
}

//------------------------------------------------
bool Shader::transmitAttrVect3(ShaderAttributeType _type, const GLfloat* _vect)
{
	if (m_attributeTypes[_type] == -1)
	{
		stringstream strstr;
		strstr << "Attribute of type " << _type << " is not registered for shader " << m_name;
        LogManager::pushEvent(new LogEvent(LogEventType::AllLogEvent,LogLevel::ERROR, strstr.str()));
		return false;
	}
	glVertexAttribPointer(m_attributeTypes[_type], 3, GL_FLOAT, GL_FALSE, 0, _vect);
	return true;
}

//------------------------------------------------
bool Shader::transmitAttrVect4(ShaderAttributeType _type, const GLfloat* _vect)
{
	if (m_attributeTypes[_type] == -1)
	{
		stringstream strstr;
		strstr << "Attribute of type " << _type << " is not registered for shader " << m_name;
        LogManager::pushEvent(new LogEvent(LogEventType::AllLogEvent, LogLevel::ERROR,strstr.str()));
		return false;
	}
	glVertexAttribPointer(m_attributeTypes[_type], 4, GL_FLOAT, GL_FALSE, 0, _vect);
	return true;
}

//------------------------------------------------
bool Shader::transmitAttrFloat(const char* _name, const GLfloat* _float)
{
	string name(_name);

	if (m_attributes.find(name) == m_attributes.end())
	{
        LogManager::pushEvent(new LogEvent(LogEventType::AllLogEvent, LogLevel::ERROR, name + " uniform is not registered for shader " + m_name));
		return false;
	}

	glVertexAttribPointer(m_attributes[_name], 1, GL_FLOAT, GL_FALSE, 0, _float);
	return true;
}

//------------------------------------------------
void Shader::enableAllAttrib()
{
	for (auto it = m_attributes.begin(); it != m_attributes.end(); ++it)
	{
		glEnableVertexAttribArray(it->second);
	}
}

//------------------------------------------------
void Shader::disableAllAttrib()
{
	for (auto it = m_attributes.begin(); it != m_attributes.end(); ++it)
	{
		glDisableVertexAttribArray(it->second);
	}
}

//------------------------------------------------
void Shader::activate(Shader* _shader)
{
	if (_shader != nullptr && s_activeShader != _shader)
	{
		_shader->activateInternal();
		s_activeShader = _shader;
	}
}
