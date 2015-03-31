#pragma once

#include <string>
#include <fstream>
#include <vector>

#include "LogManager.h"

class Helpers
{
public:
	Helpers();
	~Helpers();

public:
	static bool loadFile(const char* _fileName, std::string& _out);
	static std::vector<std::string>* splitString(const char* _src, const char _split, bool _includeEmptyString);
};

