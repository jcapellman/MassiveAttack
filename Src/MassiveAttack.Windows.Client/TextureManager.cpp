#include "TextureManager.h"

ReturnSet<int> TextureManager::LoadTexture(char * fileName)
{
	GLuint textureID;

	SDL_Surface * texture;

	texture = SDL_LoadBMP(fileName);
	
	if (texture == nullptr) {
		return ReturnSet<int>(-1, strcat(fileName, " could not be opened"));
	}

	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture->w, texture->h, 0, GL_RGB, GL_UNSIGNED_BYTE, texture->pixels);

	SDL_FreeSurface(texture);

	return textureID;
}