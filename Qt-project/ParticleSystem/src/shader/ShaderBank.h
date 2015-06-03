#ifndef SHADERBANK_H
#define SHADERBANK_H

#include "Shader.h"

#include <unordered_map>
#include <string>

/**************************************************************************
* Class: ShaderBank
* Description: Class designed to store shaders and to return them when
*						given its name, if stored.
*
**************************************************************************/
class ShaderBank
{
/////////////////////////////// PRIVATE ///////////////////////////////////
    private:
        /* Map<ShaderName, Pointer on Shader>. */
        static std::unordered_map<std::string, Shader*> s_bank;

/////////////////////////////// PUBLIC ///////////////////////////////////
    public:
    //============================= LIFECYCLE =======================================

        /**************************************************************************
        * Name:  ShaderBank()
        * Description: Default constructor.
        * Inputs: none
        **************************************************************************/
        ShaderBank();

        /**************************************************************************
        * Name:  ~ShaderBank()
        * Description: Default destructor.
        * Inputs: none
        **************************************************************************/
        virtual ~ShaderBank();

    //============================= ATTRIBUTE ACCESSORS =====================================

        /**************************************************************************
        * Name: getShader(const char* _name)
        * Description: Returns the Shader associated with the name. If the Shader
        *						doen't exist in the ShaderBank, it creates a new pointer
        *						on Shader, adds it to its own map and finally returns it.
        * Inputs:
        *			- _name : const char*, name of the Shader to return.
        * Returns:
        *			- shader : Pointer on Shader loaded from the name '_name'.
        **************************************************************************/
        static Shader* getShader(const char* _name);

};

#endif // SHADERBANK_H
