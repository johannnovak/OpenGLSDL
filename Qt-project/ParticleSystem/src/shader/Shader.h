#ifndef __SHADER_H__
#define __SHADER_H__

#include "Helpers.h"

#include "GL/glew.h"
#include <unordered_map>
#include <string>
#include <sstream>

/**************************************************************************
* Enum: ShaderAttributeType
* Description: Enum that specifies the type of attribute given to the shader.
**************************************************************************/
enum ShaderAttributeType
{
	ShaderAttributeType_POSITION = 0,
	ShaderAttributeType_COLOR,
	ShaderAttributeType_NORMAL,
	ShaderAttributeType_UV,

	ShaderAttributeType_LAST,
};

/**************************************************************************
* Enum: ShaderUniformType
* Description: Enum which specifies the type of the Uniform variable given to
*						the shader.
**************************************************************************/
enum ShaderUniformType
{
	ShaderUniformType_WORLD = 0,
	ShaderUniformType_VIEW,
	ShaderUniformType_PROJECTION,

	ShaderUniformType_LAST,
};


/**************************************************************************
* Class: Shader
* Description: Class designed implement the concept of a Shader. It serves
*						as intermediary between the program and the shaders used
*						by the graphic card when rendering a pixel. Many methods
*						have been implemented in order to register shader attributes
*						, transmit values to them, and encapsulates glX functions.
*
**************************************************************************/
class Shader
{
/////////////////////////////// PRIVATE ///////////////////////////////////
    private:
        /* Path and name of the shader. */
        std::string m_name;

        /* ID of the shader. */
        GLuint m_id;

        /* Map<ShaderAttributeString, ShaderAttributeID>, representing
         * the list of the shader attributes linked to their ID.
         */
        std::unordered_map<std::string, GLuint> m_attributes;

        /* Map<ShaderUniformAttributeString, ShaderAttributeID>, representing
         * the list of the shader uniform attributes linked to their ID.
         */
        std::unordered_map<std::string, GLuint> m_uniforms;

        /* Array linked to the enum ShaderAttributeType storing
         * the indexes of associates Enum Types */
        GLuint m_attributeTypes[ShaderAttributeType_LAST];

        /* Same as above for uniform shader variables. */
        GLuint m_uniformTypes[ShaderUniformType_LAST];

/////////////////////////////// PUBLIC ///////////////////////////////////
    public:

        /* Static pointer on the current shader activated. */
        static Shader* s_activeShader;

    public:
    //============================= LIFECYCLE =======================================

         /**************************************************************************
         * Name:  Shader()
         * Description: Default constructor.
         * Inputs: none
         **************************************************************************/
         Shader();

         /**************************************************************************
         * Name:  Shader(const int8* _shaderName)
         * Description: Parametered constructor with the name associated to the Shader.
         * Inputs:
         *			- _shaderName : const int8*, Name associated with the Shader to create.
         **************************************************************************/
         Shader(const int8* _shaderName);

         /**************************************************************************
         * Name:  ~Shader()
         * Description: Default destructor.
         * Inputs: none
         **************************************************************************/
         virtual ~Shader();

    //============================= ATTRIBUTE ACCESSORS =====================================

         /**************************************************************************
         * Name:  getName()
         * Description: Getter for the 'm_name' attribute.
         * Inputs: none
         * Returns:
         *			- m_name : Path/Name of the Shader file.
         **************************************************************************/
         std::string& getName();

         /**************************************************************************
         * Name:  getProgram()
         * Description: Getter for the 'm_id' attribute.
         * Inputs: none
         * Returns:
         *			- m_id : OpenGL ID of the shader.
         **************************************************************************/
         GLuint getProgram();

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
         bool load(const int8* _shaderName);

         /**************************************************************************
         * Name:  activate()
         * Description: Activates the current Shader OpenGL side.
         * Inputs: none
         * Returns: none
         **************************************************************************/
         void activate();


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
         GLuint getUniformLocation(const int8* _name);

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
         GLuint getUniformLocation(ShaderUniformType _type);

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
         GLuint getAttrLocation(const int8* _name);

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
         GLuint getAttrLocation(ShaderAttributeType _type);


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
         bool registerUniform(const int8* _name);

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
         bool registerUniform(const int8* _name, ShaderUniformType _type);

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
         bool registerAttribute(const int8* _name);

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
         bool registerAttribute(const int8* _name, ShaderAttributeType _type);


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
         bool transmitUniformMat4(const int8* _name, const GLfloat* _mat, GLboolean _transpose = GL_TRUE);

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
         bool transmitUniformMat4(ShaderUniformType _type, const GLfloat* _mat, GLboolean _transpose = GL_TRUE);

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
         bool transmitUniformVect3(const int8* _name, const GLfloat* _vect);

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
         bool transmitUniformVect4(const int8* _name, const GLfloat* _vect);


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
         bool transmitUniformInt(const int8* _name, const GLint _int);

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
         bool transmitUniformFloat(const int8* _name, const GLfloat _float);


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
         bool transmitAttrMat4(const int8* _name, const GLfloat* _mat);

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
         bool transmitAttrMat4(ShaderAttributeType _type, const GLfloat* _mat);


         /**************************************************************************
         * Name:  transmitAttrVect3(const int8* _name, const GLfloat* _vect)
         * Description: Encapsulation of the OpenGL function glVertexAttribPointer that
         *						registers the attribute 'm_attributes[_name]'.
         * Inputs:
         *			- _name	: const int8*, name of the shader uniform attribute to be registered.
         *			- _vect 	: Vector to transmit to the shader.
         * Returns:
         *			- True if no errors have occurred.
         *			- False otherwise.
         **************************************************************************/
         bool transmitAttrVect3(const int8* _name, const GLfloat* _vect);

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
         bool transmitAttrVect3(ShaderAttributeType _type, const GLfloat* _vect);


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
         bool transmitAttrVect4(const int8* _name, const GLfloat* _vect);

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
         bool transmitAttrVect4(ShaderAttributeType _type, const GLfloat* _vect);


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
         bool transmitAttrFloat(const int8* _name, const GLfloat* _float);


         /**************************************************************************
         * Name:  enableAllAttrib()
         * Description: For all elements of 'm_attributes', use the function
         *						glEnableVertexAttribArray.
         * Inputs: none
         * Returns: none
         **************************************************************************/
         void enableAllAttrib();

         /**************************************************************************
         * Name:  disableAllAttrib()
         * Description: For all elements of 'm_attributes', use the function
         *						glDisableVertexAttribArray.
         * Inputs: none
         * Returns: none
         **************************************************************************/
         void disableAllAttrib();

         /**************************************************************************
         * Name:  activate(Shader* _shader)
         * Description: Calls 'activateInternal' if the pointer is not null.
         * Inputs:
         *				- _shader : Pointer on shader to activate.
         * Returns: none
         **************************************************************************/
         static void activate(Shader* _shader);

/////////////////////////////// PRIVATE ///////////////////////////////////
    private:

         /**************************************************************************
         * Name:  activateInternal()
         * Description: Encapsulation method for the OpenGL function glUseProgram with
         *						the current shader.
         * Inputs: none
         * Returns: none
         **************************************************************************/
         void activateInternal();


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
         bool checkShaderError(GLuint _id, GLuint _type);

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
         bool checkProgramError(GLuint _id, GLuint _type);
};

#endif // __SHADER_H__
