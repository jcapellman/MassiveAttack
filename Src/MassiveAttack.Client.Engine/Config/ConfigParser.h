#ifndef __CONFIG_PARSER__
#define __CONFIG_PARSER__

#include "../Main.h"
#include "../Common/ReturnSet.h"

class ConfigParser
{
public:
	ConfigParser();

	ReturnSet<int> GetInt(char * key);
	ReturnSet<string> GetString(char * key);
private:
	hash_set<char *, string> _configHash;
};
#endif
