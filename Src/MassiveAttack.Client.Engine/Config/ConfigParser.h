#pragma once

#include "../Main.h"

class ConfigParser
{
public:
	ConfigParser(char * fileName) {
		_configMap = unordered_map<string, string>();

		ifstream configFile(fileName);

		string value;
		string key;

		while (configFile >> key >> value)
		{
			_configMap.emplace(key, value);
		}

		configFile.close();
	}

	int GetInt(char * key) {
		string stringValue = GetString(key);

		int intValue = atoi(const_cast<char*>(stringValue.c_str()));

		return intValue;
	}

	string GetString(char * key) {
		return _configMap.at(key);
	}
private:	
	unordered_map<string, string> _configMap;
};

