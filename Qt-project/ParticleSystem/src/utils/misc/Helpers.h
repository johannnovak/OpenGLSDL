#ifndef HELPERS_H
#define HELPERS_H

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>

#include "LogManager.h"

class Helpers
{
public:
    Helpers();
    ~Helpers();

public:
    static bool loadFile(const char* _fileName, std::string& _out);
    static std::vector<std::string>* splitString(const char* _src, const char _split, bool _includeEmptyString);

    static bool s_randInit;
    static float prand();
    static std::string uint32ToString(uint32 _value);
};

#endif
