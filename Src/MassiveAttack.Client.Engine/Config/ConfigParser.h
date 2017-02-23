#pragma once

#include "../Main.h"

#define CONFIG_XRES "XRES"
#define CONFIG_YRES "YRES"
#define CONFIG_BPP "BPP"
#define CONFIG_FULLSCREEN "FULLSCREEN"
#define CONFIG_AUDIO_NUM_CHANNELS "AUDIO_NUM_CHANNELS"

class ConfigParser
{
public:
	explicit ConfigParser(char * fileName) {
		m_configMap = unordered_map<string, string>();

		ifstream configFile(fileName);

		if (!configFile.good())
		{
			return;
		}

		string value;
		string key;

		while (configFile >> key >> value)
		{
			m_configMap.emplace(key, value);
		}

		configFile.close();
	}

	bool GetBool(char * key)
	{
		return GetString(key) == "1";
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

