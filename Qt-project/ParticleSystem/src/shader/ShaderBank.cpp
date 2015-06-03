#include "ShaderBank.h" // Implemented Class.

/* Static definition of the 's_bank' attribute. */
std::unordered_map<std::string, Shader*> ShaderBank::s_bank;

/////////////////////////////// PUBLIC ///////////////////////////////////

//============================= LIFECYCLE =======================================

/**************************************************************************
* Name:  ShaderBank()
* Description: Default constructor.
* Inputs: none
**************************************************************************/
ShaderBank::ShaderBank()
{
}

/**************************************************************************
* Name:  ~ShaderBank()
* Description: Default destructor.
* Inputs: none
**************************************************************************/
ShaderBank::~ShaderBank()
{
    for (auto elem : s_bank)
        delete elem.second;
    s_bank.clear();
}

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
Shader* ShaderBank::getShader(const char* _name)
{
    /* If the shader doesn't exist inside the bank,
     * loads a new Shader to add to the map and return.
      */
    if (s_bank.find(_name) == s_bank.end())
    {
        Shader* shader = new Shader(_name);
        s_bank[_name] = shader;
        return shader;
    }
    else
    {
        return s_bank[_name];
    }
}
