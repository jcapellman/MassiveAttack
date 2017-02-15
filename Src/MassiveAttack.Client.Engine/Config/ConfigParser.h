#pragma once

#include "../Main.h"

class ConfigParser
{
public:
	ConfigParser(char * fileName) {
		m_configMap = unordered_map<string, string>();

		ifstream configFile(fileName);

		string value;
		string key;

		while (configFile >> key >> value)
		{
			m_configMap.emplace(key, value);
		}

		configFile.close();
	}

	int GetInt(char * key) {
		auto stringValue = GetString(key);

		auto intValue = atoi(const_cast<char*>(stringValue.c_str()));

		return intValue;
	}

	string GetString(char * key) {
		auto iterator = m_configMap.find(key);

		if (iterator == m_configMap.end())
		{
			return "";
		}

		return m_configMap[key];
	}
private:	
	unordered_map<string, string> m_configMap;
};

