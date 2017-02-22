#include "SDLRenderer.h"

ReturnSet<bool> SDLRenderer::Init()
{
	int audio_rate, audio_channels;
	Uint16 audio_format;
	
	Mix_Init(MIX_INIT_MP3);

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, SDL_MIXER_BUFFER);
	
	Mix_AllocateChannels(0);
	Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);

	m_sounds = unordered_map<int, Mix_Music*>();

	return ReturnSet<bool>(true);
}

ReturnSet<int> SDLRenderer::Load(char* fileName)
{
	try {
		auto sndFile = Mix_LoadMUS(fileName);

		if (sndFile == nullptr)
		{
			throw exception(fileName);
		}

		auto index = m_sounds.size();

		m_sounds[index] = sndFile;

		return ReturnSet<int>(index);
	} catch (exception ex)
	{
		return ReturnSet<int>(ex);
	}
}

void SDLRenderer::Play(int soundID, bool loop)
{
	auto iterator = m_sounds.find(soundID);

	if (iterator == m_sounds.end())
	{
		return;
	}

	auto sound = this->m_sounds[soundID];

	if (loop)
	{
		Mix_PlayMusic(sound, 1);
	} else {
		Mix_PlayMusic(sound, 0);
	}
}

ReturnSet<bool> SDLRenderer::Shutdown()
{
	for (unsigned int x = 0; x < m_sounds.size(); x++)
	{
		Mix_FreeMusic(m_sounds[x]);
	}

	Mix_CloseAudio();

	return ReturnSet<bool>(true);
}
