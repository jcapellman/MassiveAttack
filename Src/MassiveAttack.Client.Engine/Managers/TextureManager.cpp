#include "TextureManager.h"
#include <iostream>

ReturnSet<SDL_Surface*> TextureManager::LoadTexture(char * fileName)
{
	try {
		auto * texture = IMG_Load(fileName);

		if (texture == nullptr) {
			return ReturnSet<SDL_Surface*>(exception(SDL_GetError()));
		}
		
		return ReturnSet<SDL_Surface*>(texture);
	}
	catch (exception ex) {
		return ReturnSet<SDL_Surface*>(ex);
	}
}
