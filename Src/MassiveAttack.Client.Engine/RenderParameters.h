#ifndef __RENDER_PARAMETERS__
#define __RENDER_PARAMETERS__

#include "Main.h"

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
		return this->m_parameters.at(key);
	}

	int GetParamInt(string key)
	{
		auto val = this->GetParamString(key);

		return atoi(val.c_str());
	}

	float GetParamFloat(string key)
	{
		auto val = this->GetParamString(key);

		return atof(val.c_str());
	}

	void SetParamString(string key, string val)
	{
		this->m_parameters.insert_or_assign(key, val);
	}

	void SetParamInt(string key, int val)
	{
	}

	void SetParamFloat(string key, float val)
	{
		
	}
private:
	unordered_map<string, string> m_parameters;
};
#endif
