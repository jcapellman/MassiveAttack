#include "Network.h"

ReturnSet<bool> Network::Initialize()
{
	if (SDLNet_Init() == -1) {
		return ReturnSet<bool>(false);		
	}

	return ReturnSet<bool>(true);
}
