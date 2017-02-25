#include "SDLRenderer.h"

ReturnSet<bool> SDLRenderer::Init(int numChannels)
{
	int audio_rate, audio_channels;
	Uint16 audio_format;
	
	Mix_Init(MIX_INIT_MP3);

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, SDL_MIXER_BUFFER);
	
	Mix_AllocateChannels(numChannels);
	Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);

	m_sounds = unordered_map<string, Mix_Music*>();

	return ReturnSet<bool>(true);
}

ReturnSet<bool> SDLRenderer::Load(string fileName)
{
	try {
		fileName = SOUNDS_ROOT_PATH + fileName;

		auto sndFile = Mix_LoadMUS(fileName.c_str());

		if (sndFile == nullptr)
		{
			throw exception(fileName.c_str());
		}

		m_sounds[fileName] = sndFile;

		return ReturnSet<bool>(true);
	} catch (exception ex)
	{
		return ReturnSet<bool>(ex);
	}
}

void SDLRenderer::Play(string fileName, bool loop)
{
	auto iterator = m_sounds.find(fileName);

	if (iterator == m_sounds.end())
	{
		return;
	}

	auto sound = this->m_sounds[fileName];

	if (loop)
	{
		Mix_PlayMusic(sound, 1);
	} else {
		Mix_PlayMusic(sound, 0);
	}
}

ReturnSet<bool> SDLRenderer::Shutdown()
{
	for (auto index : m_sounds)
	{
		Mix_FreeMusic(index.second);
	}

	Mix_CloseAudio();

	return ReturnSet<bool>(true);
}
