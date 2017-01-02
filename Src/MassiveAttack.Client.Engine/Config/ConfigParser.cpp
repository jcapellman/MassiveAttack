#include "ConfigParser.h"

ConfigParser::ConfigParser()
{
	this->_configHash = hash_set<char *, string>();
}

ReturnSet<int> ConfigParser::GetInt(char* key)
{
	ReturnSet<int> response(0);

	return response;
}

ReturnSet<string> ConfigParser::GetString(char* key)
{
	ReturnSet<string> response("test");

	return response;
}
