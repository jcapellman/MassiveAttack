#ifndef __LEVEL__
#define __LEVEL__

#include "Main.h"
#include "ReturnSet.h"

class Level {
	public:
		ReturnSet<bool> LoadLevel(char * fileName);
};

#endif