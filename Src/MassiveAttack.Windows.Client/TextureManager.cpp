#include "TextureManager.h"

ReturnSet<SDL_Surface*> TextureManager::LoadTexture(char * fileName)
{
	try {
		SDL_Surface * texture;

		texture = SDL_LoadBMP(fileName);

		if (texture == nullptr) {
			throw strcat(fileName, " could not be opened");
		}

		return ReturnSet<SDL_Surface*>(texture);
	}
	catch (exception ex) {
		return ReturnSet<SDL_Surface*>(ex);
	}
}