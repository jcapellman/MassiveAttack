#ifndef __RENDER_PARAMETERS__
#define __RENDER_PARAMETERS__

#include "../Main.h"

#define RPARAM_XPOS "XPOS"
#define RPARAM_YPOS "YPOS"
#define RPARAM_XROT "XROT"
#define RPARAM_YROT "YROT"
#define RPARAM_ZPOS "ZPOS"

class RENDER_PARAMETERS
{
public:
	string GetParamString(string key)
	{
		auto iterator = m_parameters.find(key);

		if (iterator == m_parameters.end())
		{
			return "";
		}

		return this->m_parameters[key];
	}

	int GetParamInt(string key)
	{
		auto val = this->GetParamString(key);

		return atoi(val.c_str());
	}

	float GetParamFloat(string key)
	{
		auto val = this->GetParamString(key);

		return stof(val.c_str());
	}

	void SetParamString(string key, string val)
	{
		this->m_parameters[key] = val;
	}

	void SetParamInt(string key, int val)
	{
		this->SetParamString(key, to_string(val));
	}

	void SetParamFloat(string key, float val)
	{
		this->SetParamString(key, to_string(val));
	}
private:
	unordered_map<string, string> m_parameters;
};
#endif
