#pragma once

#ifndef __SDLRENDERER__
#define __SDLRENDERER__

#include "ISfxRenderer.h"
#include "../Main.h"

class SDLRenderer : public ISfxRenderer {
public:
	string GetName() {
		return "SDL 1.2";
	}

	ReturnSet<bool> Init();
	ReturnSet<int> LoadSound(char * fileName);
	void PlaySound(int soundID);
	ReturnSet<bool> Shutdown();
private:
	SDL_AudioSpec * _current;
};

#endif