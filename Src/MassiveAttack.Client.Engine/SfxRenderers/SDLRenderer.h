#pragma once

#ifndef __SDLRENDERER__
#define __SDLRENDERER__

#define SDL_MIXER_BUFFER 1024

#include "ISfxRenderer.h"
#include "../Main.h"

class SDLRenderer : public ISfxRenderer {
public:
	string GetName() override
	{
		return "SDL 2";
	}

	ReturnSet<bool> Init() override;
	ReturnSet<int> LoadSound(char * fileName) override;
	void PlaySound(int soundID) override;
	ReturnSet<bool> Shutdown() override;
private:
	unordered_map<int, Mix_Music*> m_sounds;
};

#endif