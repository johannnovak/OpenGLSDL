#include "Helpers.h"

using namespace std;

bool Helpers::s_randInit = false;

Helpers::Helpers()
{
}


Helpers::~Helpers()
{
}

bool Helpers::loadFile(const int8* _fileName, string& _out)
{
    LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_DEBUG, "Loading file '"+ string(_fileName) +"'...");

    ifstream file(_fileName);
    _out.clear();

    if (file.is_open())
    {
        file.seekg(0, std::ios::end);
        _out.reserve(file.tellg());
        file.seekg(0, std::ios::beg);

        _out.assign((std::istreambuf_iterator<int8>(file)),
                    std::istreambuf_iterator<int8>());

        file.close();

        LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_DEBUG, "File '"+ string(_fileName) +"' successfully loaded.");
        return true;
    }
    else
    {
        LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_ERROR, "Could not open file '" + string(_fileName) +"'.");
        return false;
    }
}

vector<string>* Helpers::splitString(const int8* _src, const int8 _split, bool _includeEmptyString)
{
    vector<string>* result = new vector<string>();
    string temp = "";
    for (uint32 i = 0; _src[i] != '\0'; ++i)
    {
        if (_src[i] == _split)
        {
            if (!temp.empty() || _includeEmptyString)
            {
                result->push_back(temp);
            }
            temp = "";
        }
        else
        {
            temp += _src[i];
        }
    }

    if (temp[0] != _split)
    {
        if (!temp.empty() || _includeEmptyString)
            result->push_back(temp);
    }

    return result;
}

float32 Helpers::prand()
{
    if (!s_randInit)
    {
        srand(time(NULL));
        s_randInit = true;
    }

    return (float32)rand() / (float32)RAND_MAX;
}

std::string Helpers::uint32ToString(uint32 _value)
{
    std::stringstream ss;
    ss << _value;
    ss.str("");
    return ss.str();
}
