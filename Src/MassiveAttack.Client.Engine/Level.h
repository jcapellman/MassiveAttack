#ifndef __LEVEL__
#define __LEVEL__

#include "Main.h"
#include "Common/ReturnSet.h"

class Level {
	public:
		ReturnSet<bool> LoadLevel(char * fileName);
};

#endif