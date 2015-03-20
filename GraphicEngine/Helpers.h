#pragma once

#include <string>
#include <fstream>

#include "LogManager.h"

class Helpers
{
public:
	Helpers();
	~Helpers();

public:
	static bool loadFile(const char* _fileName, std::string& _out);
};

