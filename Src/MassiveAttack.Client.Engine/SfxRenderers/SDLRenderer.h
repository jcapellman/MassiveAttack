#pragma once

#ifndef __SDLRENDERER__
#define __SDLRENDERER__

#define SDL_MIXER_BUFFER 1024

#include "ISfxRenderer.h"
#include "../Main.h"

class ModManager;

class SDLRenderer : public ISfxRenderer {
public:
	string GetName() override
	{
		return "SDL 2";
	}

	ReturnSet<bool> Init(int numChannels, ModManager * modManager) override;
	ReturnSet<bool> LoadSound(string fileName) override;
	ReturnSet<bool> LoadMusic(string fileName) override;
	void PlaySound(string fileName, bool loop = false) override;
	void PlayMusic() override;
	ReturnSet<bool> Shutdown() override;
private:
	unordered_map<string, Mix_Chunk*> m_sounds;
	Mix_Music * m_music;

	ModManager * m_modManager;
};

#endif