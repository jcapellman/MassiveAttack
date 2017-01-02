#include "TextureManager.h"

ReturnSet<SDL_Surface*> TextureManager::LoadTexture(char * fileName)
{
	try {
		SDL_Surface * texture = SDL_LoadBMP(fileName);

		if (texture == NULL) {
			throw SDL_GetError();
		}

		return ReturnSet<SDL_Surface*>(texture);
	}
	catch (exception ex) {
		return ReturnSet<SDL_Surface*>(ex);
	}
}