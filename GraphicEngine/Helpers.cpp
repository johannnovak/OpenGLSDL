#include "Helpers.h"

using namespace std;

Helpers::Helpers()
{
}


Helpers::~Helpers()
{
}

bool Helpers::loadFile(const char* _fileName, string& _out)
{
	ifstream file(_fileName);
	_out.clear();

	if (file.is_open())
	{
		file.seekg(0, std::ios::end);
		_out.reserve(file.tellg());
		file.seekg(0, std::ios::beg);

		_out.assign((std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>());

		file.close();

		return true;
	}
	else
	{
		LogManager::showError(("Can't open file " + string(_fileName)).c_str());
		return false;
	}
}

vector<string>* Helpers::splitString(const char* _src, const char _split, bool _includeEmptyString)
{
	vector<string>* result = new vector<string>();
	string temp = "";
	for (unsigned int i = 0; _src[i] != '\0'; ++i)
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