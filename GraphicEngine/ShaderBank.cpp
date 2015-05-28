#include "ShaderBank.h"

std::unordered_map<std::string, Shader*> ShaderBank::s_bank;


ShaderBank::ShaderBank()
{
}


ShaderBank::~ShaderBank()
{
	for (auto elem : s_bank)
	{
		delete elem.second;
	}
	s_bank.clear();
}

Shader* ShaderBank::getShader(const char* _name)
{
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
