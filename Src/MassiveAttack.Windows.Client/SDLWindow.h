#ifndef _SDLWINDOW_
#define _SDLWINDOW_

#include "Main.h"

#include <SDL/SDL.h>
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "GLu32.lib")
#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLMain.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")

class SDLWindow
{
public:
	void Init();

	void Render();

	SDLWindow()
	{
		this->width = 1024;
		this->height = 768;
	}
private:
	void InitGL();
	void ResizeWindow();

	SDL_Surface *surface;

	int width;
	int height;
};

#endif