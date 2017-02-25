#include "SDLRenderer.h"

ReturnSet<bool> SDLRenderer::Init(int numChannels)
{
	int audio_rate, audio_channels;
	Uint16 audio_format;
	
	Mix_Init(MIX_INIT_MP3);

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, SDL_MIXER_BUFFER);
	
	Mix_AllocateChannels(numChannels);
	Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);

	m_sounds = unordered_map<string, Mix_Chunk*>();

	return ReturnSet<bool>(true);
}

ReturnSet<bool> SDLRenderer::LoadSound(string fileName)
{
	try {
		fileName = SOUNDS_ROOT_PATH + fileName;

		auto sndFile = Mix_LoadWAV(fileName.c_str());

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

ReturnSet<bool> SDLRenderer::LoadMusic(string fileName)
{
	try {
		fileName = MUSIC_ROOT_PATH + fileName;

		auto sndFile = Mix_LoadMUS(fileName.c_str());

		if (sndFile == nullptr)
		{
			throw exception(fileName.c_str());
		}

		if (m_music != nullptr)
		{
			Mix_FreeMusic(m_music);
		}

		m_music = sndFile;

		return ReturnSet<bool>(true);
	}
	catch (exception ex)
	{
		return ReturnSet<bool>(ex);
	}
}

void SDLRenderer::PlayMusic()
{
	if (m_music == nullptr)
	{
		return;
	}

	Mix_PlayMusic(m_music, 1);
}

void SDLRenderer::PlaySound(string fileName, bool loop)
{
	auto iterator = m_sounds.find(SOUNDS_ROOT_PATH + fileName);

	if (iterator == m_sounds.end())
	{
		return;
	}

	auto sound = this->m_sounds[SOUNDS_ROOT_PATH + fileName];

	if (loop)
	{
		Mix_PlayChannel(-1, sound, 1);
	} else {
		Mix_PlayChannel(-1, sound, 0);
	}
}

ReturnSet<bool> SDLRenderer::Shutdown()
{
	for (auto index : m_sounds)
	{
		Mix_FreeChunk(index.second);
	}

	Mix_FreeMusic(m_music);

	Mix_CloseAudio();

	return ReturnSet<bool>(true);
}
