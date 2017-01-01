#ifndef _SDLWINDOW_
#define _SDLWINDOW_

#include "Main.h"
#include "TextureManager.h"
#include "Level.h"
#include "GfxRenderers/IGfxRenderer.h"

class SDLWindow
{
public:
	void Init();

	void MainLoop();

	SDLWindow()
	{
		this->width = 1024;
		this->height = 768;

		this->xpos = 1.5f;
		this->zpos = 6.0f;
		this->yrot = 0.0f;
	}
private:
	IGfxRenderer * _gfxRenderer;

	void handle_key_down(SDL_keysym* keysym);
	void process_events(void);

	void Render();
	void Quit();

	SDL_Surface *surface;

	int width;
	int height;

	TextureManager textureManager;
	int textureID;

	const float piover180 = 0.0174532925f;
	float heading;
	float xpos;
	float zpos;

	float	yrot;
	float walkbias = 0;
	float walkbiasangle = 0;
	float lookupdown = 0.0f;
	float	z = 0.0f;
};

#endif