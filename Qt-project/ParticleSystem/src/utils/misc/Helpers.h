#ifndef __HELPERS_H__
#define __HELPERS_H__

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
    static bool loadFile(const int8* _fileName, std::string& _out);
    static std::vector<std::string>* splitString(const int8* _src, const int8 _split, bool _includeEmptyString);

    static bool s_randInit;
    static float32 prand();
    static std::string uint32ToString(uint32 _value);
};

#endif // __HELPERS_H__
