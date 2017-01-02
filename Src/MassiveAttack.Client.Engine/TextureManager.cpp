#include "TextureManager.h"
#include <iostream>

ReturnSet<SDL_Surface*> TextureManager::LoadTexture(char * fileName)
{
	try {
		SDL_Surface * texture = SDL_LoadBMP(fileName);

		if (texture == NULL) {
			cout << SDL_GetError() << endl;

			return ReturnSet<SDL_Surface*>(exception(SDL_GetError()));
		}
		
		return ReturnSet<SDL_Surface*>(texture);
	}
	catch (exception ex) {
		return ReturnSet<SDL_Surface*>(ex);
	}
}
