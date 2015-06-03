#include "Shader.h" // Implemented class.

Shader* Shader::s_activeShader = nullptr;

using namespace std;

/////////////////////////////// PUBLIC ///////////////////////////////////

//============================= LIFECYCLE =======================================

/**************************************************************************
* Name:  Shader()
* Description: Default constructor.
* Inputs: none
**************************************************************************/
Shader::Shader() : m_name(), m_attributes(), m_uniforms()
{}

/**************************************************************************
* Name:  Shader(const int8* _shaderName)
* Description: Parametered constructor with the name associated to the Shader.
*						It loads the shader associated with '_shaderName'.
* Inputs:
*			- _shaderName : const int8*, Name associated with the Shader to create.
**************************************************************************/
Shader::Shader(const int8* _shaderName) : m_name(), m_attributes(), m_uniforms()
{
    load(_shaderName);
}

/**************************************************************************
* Name:  ~Shader()
* Description: Default destructor.
* Inputs: none
**************************************************************************/
Shader::~Shader()
{
    glDeleteProgram(m_id);
}

//============================= ATTRIBUTE ACCESSORS =====================================

/**************************************************************************
* Name:  getName()
* Description: Getter for the 'm_name' attribute.
* Inputs: none
* Returns:
*			- m_name : Path/Name of the Shader file.
**************************************************************************/
string& Shader::getName()
{
    return m_name;
}

/**************************************************************************
* Name:  getProgram()
* Description: Getter for the 'm_id' attribute.
* Inputs: none
* Returns:
*			- m_id : OpenGL ID of the shader.
**************************************************************************/
GLuint Shader::getProgram()
{
    return m_id;
}

//============================= OPERATIONS ==============================================

/**************************************************************************
* Name:  load(const int8* _shaderName)
* Description: Complete loading of the file. It loads both .vs and .fs files
*					then create the OpenGL associated program, creates the
*					associated GLShader, pre-compiles the files to check errors,
*					attaches and links the program to the shaders and finally
*					check for any other program errors.
* Inputs:
*			- _shaderName : Path/Name of the Shader .vf and .fs files.
* Returns:
*			- True if no errors have occurred during the loading.
*			- false otherwise.
**************************************************************************/
bool Shader::load(const int8* _shaderName)
{
    LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_DEBUG, "Loading Shader '"+ string(_shaderName) +"'...");

    /* Initializes the values of the types. */
    for (uint32 i = 0; i < ShaderAttributeType_LAST; ++i)
        m_attributeTypes[i] = -1;
    for (uint32 i = 0; i < ShaderUniformType_LAST; ++i)
        m_uniformTypes[i] = -1;

    /* Gets the name as a string object. */
    m_name = string(_shaderName);

    /* Creates the .vs and .fs files string names. */
    string vs_file = m_name + ".vs";
    string fs_file = m_name + ".fs";

    string vs_str, fs_str;
    const int8* vs_ptr, *fs_ptr;

    /* Loads the two shader files. */
    Helpers::loadFile(vs_file.c_str(), vs_str);
    Helpers::loadFile(fs_file.c_str(), fs_str);

    vs_ptr = vs_str.c_str();
    fs_ptr = fs_str.c_str();

    /* Creates a program and gets back the ID. */
    m_id = glCreateProgram();

    /* Creates the two shaders OpenGL side. */
    GLuint vs_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs_id = glCreateShader(GL_FRAGMENT_SHADER);

    /* Compiling Vertex Shader. */
    glShaderSource(vs_id, 1, &vs_ptr, NULL);
    glCompileShader(vs_id);

    /* Checks and logs any error. */
    if (!checkShaderError(vs_id, GL_COMPILE_STATUS))
    {
        glDeleteProgram(m_id);
        glDeleteShader(vs_id);
        glDeleteShader(fs_id);

        return false;
    }

    /* Compiles Fragment Shader. */
    glShaderSource(fs_id, 1, &fs_ptr, NULL);
    glCompileShader(fs_id);

    /* Checks and logs any error. */
    if (!checkShaderError(fs_id, GL_COMPILE_STATUS))
    {
        glDeleteProgram(m_id);
        glDeleteShader(vs_id);
        glDeleteShader(fs_id);

        return false;
    }

    /* Attaches Shaders. */
    glAttachShader(m_id, vs_id);
    glAttachShader(m_id, fs_id);

    /* Links the program. */
    glLinkProgram(m_id);

    /* Checks and logs any error. */
    if (!checkProgramError(m_id, GL_LINK_STATUS))
    {
        glDeleteProgram(m_id);
        glDeleteShader(vs_id);
        glDeleteShader(fs_id);

        return false;
    }

    vs_ptr = nullptr;
    fs_ptr = nullptr;

    LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_DEBUG, "Shader '"+ string(_shaderName) +"' loaded.");

    return true;
}

/**************************************************************************
* Name:  activate()
* Description: Activates the current Shader OpenGL side.
* Inputs: none
* Returns: none
**************************************************************************/
void Shader::activate()
{
    Shader::activate(this);
}


/**************************************************************************
* Name:  getUniformLocation(const int8* _name)
* Description: Returns the ID of the uniform shader variable associated
*					with the '_name' parameter.
* Inputs:
*			- _name : Name of the uniform variable whose ID have to be returned.
* Returns:
*			- -1 if no uniform shader attributes were found.
*			- The ID of the uniform shader attribute of the current Shader with
*				the name '_name'.
**************************************************************************/
GLuint Shader::getUniformLocation(const int8* _name)
{
    string name(_name);

    if (m_uniforms.find(name) == m_uniforms.end())
    {
        LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_ERROR, name + " attribute is not registered for shader " + m_name);
        return -1;
    }

    return m_uniforms[name];
}

/**************************************************************************
* Name:  getUniformLocation(ShaderUniformType _type)
* Description: Returns the ID of the uniform shader variable associated
*					with the ShaderUniformType parameter.
* Inputs:
*			- _type : Type of the uniform shader variable.
* Returns:
*			- -1 if '_type'- is not valid.
*			- The OpenGL Shader ID of the uniform shader variable associated
*				wih '_type'.
**************************************************************************/
GLuint Shader::getUniformLocation(ShaderUniformType _type)
{
    if (_type != ShaderUniformType_LAST)
    {
        return m_uniformTypes[_type];
    }

    return -1;
}

/**************************************************************************
* Name:  getAttrLocation(const int8* _name)
* Description: Returns the ID of the shader variable associated
*					with the '_name' parameter.
* Inputs:
*			- _name : Name of the variable whose ID have to be returned.
* Returns:
*			- -1 if no shader attributes were found.
*			- The ID of the shader attribute of the current Shader with
*				the name '_name'.
**************************************************************************/
GLuint Shader::getAttrLocation(const int8* _name)
{
    string name(_name);

    if (m_attributes.find(name) == m_attributes.end())
    {
        LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_ERROR, name + " attribute is not registered for shader " + m_name);
        return -1;
    }

    return m_attributes[name];
}

/**************************************************************************
* Name:  getAttrLocation(ShaderAttributeType _type)
* Description: Returns the ID of the uniform shader variable associated
*					with the ShaderAttributeType parameter.
* Inputs:
*			- _type : Type of the uniform shader variable.
* Returns:
*			- -1 if '_type'- is not valid.
*			- The OpenGL Shader ID of the uniform shader variable associated
*				wih '_type'.
**************************************************************************/
GLuint Shader::getAttrLocation(ShaderAttributeType _type)
{
    if (_type != ShaderAttributeType_LAST)
    {
        return m_attributeTypes[_type];
    }

    return -1;
}

/**************************************************************************
* Name:  registerUniform(const int8* _name)
* Description: Registers in the Shader through glGetUniformLocation(), the
*					uniform attribute named '_name'.
* Inputs:
*			- _name : Name of the uniform shader attribute to be registered.
* Returns:
*			- True if no errors have occurred.
*			- False otherwise.
**************************************************************************/
bool Shader::registerUniform(const int8* _name)
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
        LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_ERROR, name + " uniform does not exist in shader " + m_name);
        return false;
    }

    m_uniforms[name] = id;
    return true;
}

/**************************************************************************
* Name:  registerUniform(const int8* _name, ShaderUniformType _type)
* Description: Registers in the Shader through glGetUniformLocation(), the
*					uniform attribute named '_name' and stores it inside the
*					'm_uniformTypes' attribute.
* Inputs:
*			- _name : Name of the uniform shader attribute to be registered.
*			- _type : ShaderUniformType associated with the uniform attribute.
* Returns:
*			- True if no errors have occurred.
*			- False otherwise.
**************************************************************************/
bool Shader::registerUniform(const int8* _name, ShaderUniformType _type)
{
    bool success = registerUniform(_name);
    if (success)
    {
        m_uniformTypes[_type] = getUniformLocation(_name);
    }

    return success;
}

/**************************************************************************
* Name:  registerAttribute(const int8* _name)
* Description: Registers in the Shader through glGetAttribLocation(), the
*						attribute named '_name'.
* Inputs:
*			- _name : Name of the shader attribute to be registered.
* Returns:
*			- True if no errors have occurred.
*			- False otherwise.
**************************************************************************/
bool Shader::registerAttribute(const int8* _name)
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
        LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_ERROR, name + " uniform does not exist in shader " + m_name);
        return false;
    }

    m_attributes[name] = id;
    return true;
}

/**************************************************************************
* Name:  registerAttribute(const int8* _name, ShaderUniformType _type)
* Description: Registers in the Shader through glGetAttribLocation(), the
*						attribute named '_name' and stores it inside the
*						'm_uniformTypes' attribute.
* Inputs:
*			- _name : Name of the shader attribute to be registered.
*			- _type : ShaderAttributeType associated with the attribute.
* Returns:
*			- True if no errors have occurred.
*			- False otherwise.
**************************************************************************/
bool Shader::registerAttribute(const int8* _name, ShaderAttributeType _type)
{
    bool registered = registerAttribute(_name);
    if (registered == true)
    {
        m_attributeTypes[_type] = getAttrLocation(_name);
        return true;
    }

    return false;
}

/**************************************************************************
* Name:  transmitUniformMat4(const int8* _name, const GLfloat* _mat, GLboolean _transpose = GL_TRUE)
* Description: Encapsulation of the OpenGL function glUniformMatrix4fv that registers the uniform
*						attribute 'm_uniforms[_name]' as a 4x4 Matrix.
* Inputs:
*			- _name 			: Name of the shader uniform attribute to be registered.
*			- _mat        	: Matrix to transmit to the shader.
*			- _transpose  	: required attribute for glUniformMatrix4fv. Default value is GL_TRUE.
* Returns:
*			- True if no errors have occurred.
*			- False otherwise.
**************************************************************************/
bool Shader::transmitUniformMat4(const int8* _name, const GLfloat* _mat, GLboolean _transpose)
{
    string name(_name);

    if (m_uniforms.find(name) == m_uniforms.end())
    {
        LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_ERROR, name + " uniform is not registered for shader " + m_name);
        return false;
    }

    glUniformMatrix4fv(m_uniforms[name], 1, _transpose, _mat);

    return true;
}

/**************************************************************************
* Name:  transmitUniformMat4(ShaderUniformType _type, const GLfloat* _mat, GLboolean _transpose = GL_TRUE)
* Description: Encapsulation of the OpenGL function glUniformMatrix4fv that registers the uniform
*						attribute 'm_uniformsType[_type]' as a 4x4 Matrix.
* Inputs:
*			- _type 			: ShaderUniformType of the shader uniform attribute to be registered.
*			- _mat        	: Matrix to transmit to the shader.
*			- _transpose  	: required attribute for glUniformMatrix4fv. Default value is GL_TRUE.
* Returns:
*			- True if no errors have occurred.
*			- False otherwise.
**************************************************************************/
bool Shader::transmitUniformMat4(ShaderUniformType _type, const GLfloat* _mat, GLboolean _transpose)
{
    if (m_uniformTypes[_type] == -1)
    {
        stringstream strstr;
        strstr << "Uniform type " << _type << " is not registered for shader " << m_name;
        LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT,LogLevel::LogLevel_ERROR, strstr.str());

        return false;
    }

    glUniformMatrix4fv(m_uniformTypes[_type], 1, _transpose, _mat);

    return true;
}

/**************************************************************************
* Name:  transmitUniformVect3(const int8* _name, const GLfloat* _vect)
* Description: Encapsulation of the OpenGL function glUniform3fv that registers the uniform
*						attribute 'm_uniforms[_name]' as a vector 3*1.
* Inputs:
*			- _name	: const int8*, name of the shader uniform attribute to be registered.
*			- _vect 	: Vector to transmit to the shader.
* Returns:
*			- True if no errors have occurred.
*			- False otherwise.
**************************************************************************/
bool Shader::transmitUniformVect3(const int8* _name, const GLfloat* _vect)
{
    string name(_name);

    if (m_uniforms.find(name) == m_uniforms.end())
    {
        LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_ERROR, name + " uniform is not registered for shader " + m_name);
        return false;
    }

    glUniform3fv(m_uniforms[name], 1, _vect);
    return true;
}

/**************************************************************************
* Name:  transmitUniformVect4(const int8* _name, const GLfloat* _vect)
* Description: Encapsulation of the OpenGL function glUniform4fv that registers the uniform
*						attribute 'm_uniforms[_name]' as a vector 4*1.
* Inputs:
*			- _name	: const int8*, name of the shader uniform attribute to be registered.
*			- _vect 	: Vector to transmit to the shader.
* Returns:
*			- True if no errors have occurred.
*			- False otherwise.
**************************************************************************/
bool Shader::transmitUniformVect4(const int8* _name, const GLfloat* _vect)
{
    string name(_name);

    if (m_uniforms.find(name) == m_uniforms.end())
    {
        LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_ERROR, name + " uniform is not registered for shader " + m_name);
        return false;
    }

    glUniform4fv(m_uniforms[name], 1, _vect);
    return true;
}

/**************************************************************************
* Name:  transmitUniformInt(const int8* _name, const GLint* _int)
* Description: Encapsulation of the OpenGL function glUniform1i that registers the uniform
*						attribute 'm_uniforms[_name]'.
* Inputs:
*			- _name	: const int8*, name of the shader uniform attribute to be registered.
*			- _int 	: Integer to transmit to the shader.
* Returns:
*			- True if no errors have occurred.
*			- False otherwise.
**************************************************************************/
bool Shader::transmitUniformInt(const int8* _name, const GLint _int)
{
    string name(_name);

    if (m_uniforms.find(name) == m_uniforms.end())
    {
        LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_ERROR, name + " uniform is not registered for shader " + m_name);
        return false;
    }

    glUniform1i(m_uniforms[name], _int);
    return true;
}

/**************************************************************************
* Name:  transmitUniformFloat(const int8* _name, const GLfloat* _float)
* Description: Encapsulation of the OpenGL function glUniform1f that registers the uniform
*						attribute 'm_uniforms[_name]'.
* Inputs:
*			- _name		: const int8*, of the shader uniform attribute to be registered.
*			- _float 	: Float to transmit to the shader.
* Returns:
*			- True if no errors have occurred.
*			- False otherwise.
**************************************************************************/
bool Shader::transmitUniformFloat(const int8* _name, const GLfloat _float)
{
    string name(_name);

    if (m_uniforms.find(name) == m_uniforms.end())
    {
        LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_ERROR, name + " uniform is not registered for shader " + m_name);
        return false;
    }

    glUniform1f(m_uniforms[name], _float);
    return true;
}

/**************************************************************************
* Name:  transmitAttrMat4(const int8* _name, const GLfloat* _mat)
* Description: Not implemented yet.
* Inputs:
*			- _name	: const int8*, name of the shader attribute to be registered.
*			- _mat 	: Matrix to transmit to the shader.
* Returns:
*			- True if no errors have occurred.
*			- False otherwise.
**************************************************************************/
bool Shader::transmitAttrMat4(const int8* _name, const GLfloat* _mat)
{
    LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_ERROR, "transmitAttrMat4 is not implemented yet...");
    return false;
}

/**************************************************************************
* Name:  transmitAttrMat4((ShaderAttributeType _type, const GLfloat* _mat)
* Description: Not implemented yet.
* Inputs:
*			- _type 	: ShaderAttributeType of the shader attribute to be registered.
*			- _mat 	: Matrix to transmit to the shader.
* Returns:
*			- True if no errors have occurred.
*			- False otherwise.
**************************************************************************/
bool Shader::transmitAttrMat4(ShaderAttributeType _type, const GLfloat* _mat)
{
    LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT,LogLevel::LogLevel_ERROR, "transmitAttrMat4 is not implemented yet...");
    return false;
}

/**************************************************************************
* Name:  transmitAttrMat4(const int8* _name, const GLfloat* _mat)
* Description: Not implemented yet.
* Inputs:
*			- _name	: const int8*, name of the shader uniform attribute to be registered.
*			- _mat 	: Matrix to transmit to the shader.
* Returns:
*			- True if no errors have occurred.
*			- False otherwise.
**************************************************************************/
bool Shader::transmitAttrVect3(const int8* _name, const GLfloat* _vect)
{
    string name(_name);

    if (m_attributes.find(name) == m_attributes.end())
    {
        LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT,LogLevel::LogLevel_ERROR, name + " uniform is not registered for shader " + m_name);
        return false;
    }

    glVertexAttribPointer(m_attributes[name], 3, GL_FLOAT, GL_FALSE, 0, _vect);
    return true;
}

/**************************************************************************
* Name:  transmitAttrVect3(ShaderAttributeType _type, const GLfloat* _vect)
* Description: Encapsulation of the OpenGL function glVertexAttribPointer that
*						registers the attribute 'm_attributes[_name]'.
* Inputs:
*			- _type 	: ShaderAttributeType of the shader attribute to be registered.
*			- _vect 	: Vector to transmit to the shader.
* Returns:
*			- True if no errors have occurred.
*			- False otherwise.
**************************************************************************/
bool Shader::transmitAttrVect3(ShaderAttributeType _type, const GLfloat* _vect)
{
    if (m_attributeTypes[_type] == -1)
    {
        stringstream strstr;
        strstr << "Attribute of type " << _type << " is not registered for shader " << m_name;
        LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT,LogLevel::LogLevel_ERROR, strstr.str());
        return false;
    }
    glVertexAttribPointer(m_attributeTypes[_type], 3, GL_FLOAT, GL_FALSE, 0, _vect);
    return true;
}


/**************************************************************************
* Name:  transmitAttrVect4(const int8* _name, const GLfloat* _vect)
* Description: Encapsulation of the OpenGL function glVertexAttribPointer that
*						registers the attribute 'm_attributes[_name]'.
* Inputs:
*			- _name	: const int8*, name of the shader uniform attribute to be registered.
*			- _vect 	: Vector to transmit to the shader.
* Returns:
*			- True if no errors have occurred.
*			- False otherwise.
**************************************************************************/
bool Shader::transmitAttrVect4(const int8* _name, const GLfloat* _vect)
{
    string name(_name);

    if (m_attributes.find(name) == m_attributes.end())
    {
        LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT,LogLevel::LogLevel_ERROR, name + " uniform is not registered for shader " + m_name);
        return false;
    }

    glVertexAttribPointer(m_attributes[name], 4, GL_FLOAT, GL_FALSE, 0, _vect);
    return true;
}

/**************************************************************************
* Name:  transmitAttrVect4(ShaderAttributeType _type, const GLfloat* _vect)
* Description: Encapsulation of the OpenGL function glVertexAttribPointer that
*						registers the attribute 'm_attributes[_name]'.
* Inputs:
*			- _type 	: ShaderAttributeType of the shader attribute to be registered.
*			- _vect 	: Vector to transmit to the shader.
* Returns:
*			- True if no errors have occurred.
*			- False otherwise.
**************************************************************************/
bool Shader::transmitAttrVect4(ShaderAttributeType _type, const GLfloat* _vect)
{
    if (m_attributeTypes[_type] == -1)
    {
        stringstream strstr;
        strstr << "Attribute of type " << _type << " is not registered for shader " << m_name;
        LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_ERROR,strstr.str());
        return false;
    }
    glVertexAttribPointer(m_attributeTypes[_type], 4, GL_FLOAT, GL_FALSE, 0, _vect);
    return true;
}

/**************************************************************************
* Name:  transmitAttrFloat(const int8* _name, const GLfloat* _float)
* Description: Encapsulation of the OpenGL function glVertexAttribPointer that
*						registers attribute 'm_uniforms[_name]'.
* Inputs:
*			- _name	: const int8*, name of the shader uniform attribute to be registered.
*			- _float 	: Float to transmit to the shader.
* Returns:
*			- True if no errors have occurred.
*			- False otherwise.
**************************************************************************/
bool Shader::transmitAttrFloat(const int8* _name, const GLfloat* _float)
{
    string name(_name);

    if (m_attributes.find(name) == m_attributes.end())
    {
        LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_ERROR, name + " uniform is not registered for shader " + m_name);
        return false;
    }

    glVertexAttribPointer(m_attributes[_name], 1, GL_FLOAT, GL_FALSE, 0, _float);
    return true;
}

/**************************************************************************
* Name:  enableAllAttrib()
* Description: For all elements of 'm_attributes', use the function
*						glEnableVertexAttribArray.
* Inputs: none
* Returns: none
**************************************************************************/
void Shader::enableAllAttrib()
{
    for (auto it = m_attributes.begin(); it != m_attributes.end(); ++it)
    {
        glEnableVertexAttribArray(it->second);
    }
}

/**************************************************************************
* Name:  disableAllAttrib()
* Description: For all elements of 'm_attributes', use the function
*						glDisableVertexAttribArray.
* Inputs: none
* Returns: none
**************************************************************************/
void Shader::disableAllAttrib()
{
    for (auto it = m_attributes.begin(); it != m_attributes.end(); ++it)
    {
        glDisableVertexAttribArray(it->second);
    }
}

/**************************************************************************
* Name:  activate(Shader* _shader)
* Description: Calls 'activateInternal' if the pointer is not null.
* Inputs:
*				- _shader : Pointer on shader to activate.
* Returns: none
**************************************************************************/
void Shader::activate(Shader* _shader)
{
    if (_shader != nullptr && s_activeShader != _shader)
    {
        _shader->activateInternal();
        s_activeShader = _shader;
    }
}

/////////////////////////////// PRIVATE ///////////////////////////////////

/**************************************************************************
* Name:  activateInternal()
* Description: Encapsulation method for the OpenGL function glUseProgram with
*						the current shader.
* Inputs: none
* Returns: none
**************************************************************************/
void Shader::activateInternal()
{
    glUseProgram(m_id);
}

/**************************************************************************
* Name:  checkShaderError(GLuint _id, GLuint _type)
* Description: Check if any error occured when pre-compiling the shader code.
*						It encapsulates the OpenGL function glGetShaderIV
* Inputs:
*				- _id  	: GLUint, ID of the shader to check.
*				- _type	: GLUint, OpenGL constant. Set normally to GL_COMPILE_STATUS.
* Returns:
*				- True if not error occurred.
*				- False otherwise.
**************************************************************************/
bool Shader::checkShaderError(GLuint _id, GLuint _type)
{
    GLint status, logSize;
    int8* log = NULL;

    glGetShaderiv(_id, _type, &status);
    if (status != GL_TRUE)
    {
        glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &logSize);
        log = new int8[logSize + 1];
        glGetShaderInfoLog(_id, logSize, &logSize, log);
        log[logSize] = '\0';
        LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT,LogLevel::LogLevel_ERROR, "Error in fs/vs: " + string(log));
        delete[] log;
        log = NULL;
        return false;
    }

    LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_DEBUG, "Shader with id '"+ to_string(_id) +"'' has no errors.");
    return true;
}

/**************************************************************************
* Name:  checkShaderError(GLuint _id, GLuint _type)
* Description: Check if any error occured when linking the shader to the
*						program. It encapsulates the OpenGL function glGetShaderIV.
* Inputs:
*				- _id  	: GLUint, ID of the shader to check.
*				- _type	: GLUint, OpenGL constant. Set normally to GL_LINK_STATUS.
* Returns:
*				- True if not error occurred.
*				- False otherwise.
**************************************************************************/
bool Shader::checkProgramError(GLuint _id, GLuint _type)
{
    GLint status, logSize;
    int8* log = NULL;

    glGetProgramiv(_id, _type, &status);
    if (status != GL_TRUE)
    {
        glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &logSize);
        log = new int8[logSize + 1];
        glGetProgramInfoLog(_id, logSize, &logSize, log);
        log[logSize] = '\0';
        LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_ERROR, "Error in fs/vs: " + string(log));
        delete[] log;
        log = NULL;
        return false;
    }

    LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_DEBUG, "Program attached to shaders has no errors.");
    return true;
}
