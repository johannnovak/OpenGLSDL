#ifndef SHADERBANK_H
#define SHADERBANK_H

#include <unordered_map>
#include <string>

#include "Shader.h"

class ShaderBank
{
public:
	ShaderBank();
	virtual ~ShaderBank();

	static Shader* getShader(const char* _name);


private:
	static std::unordered_map<std::string, Shader*> s_bank;
};

#endif
