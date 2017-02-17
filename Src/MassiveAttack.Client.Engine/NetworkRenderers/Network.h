#pragma once

#include "Main.h"

#include <SDL\SDL_net.h>
#include "Common/ReturnSet.h"

#pragma comment(lib, "SDL_net.lib")

class Network
{
public:
	ReturnSet<bool> Initialize();
};
