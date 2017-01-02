#include "SDLRenderer.h"

ReturnSet<bool> SDLRenderer::Init()
{
	SDL_AudioSpec *desired = nullptr;

	desired->freq = 44100;

	desired->format = AUDIO_S16LSB;

	desired->channels = 2;

	desired->samples = 8192;

	if (SDL_OpenAudio(desired, _current) < 0) {
		free(desired);

		return ReturnSet<bool>(false);
	}

	free(desired);

	return ReturnSet<bool>(true);
}

ReturnSet<int> SDLRenderer::LoadSound(char* fileName)
{
	try {
		SDL_AudioSpec wav_spec;
		Uint32 wav_length;
		Uint8 *wav_buffer;

		if (SDL_LoadWAV(fileName, &wav_spec, &wav_buffer, &wav_length) == NULL) {
			throw SDL_GetError();
		}

		return ReturnSet<int>(0);
	} catch (exception ex)
	{
		return ReturnSet<int>(ex);
	}
}

void SDLRenderer::PlaySoundW(int soundID)
{

}

ReturnSet<bool> SDLRenderer::Shutdown()
{
	free(_current);
	SDL_CloseAudio();

	return ReturnSet<bool>(true);
}
