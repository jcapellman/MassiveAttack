#include "Main.h"
#include "SDLWindow.h"

static void quit_tutorial(int code)
{
	SDL_Quit();

	exit(code);
}



int main(int argc, char *argv[])
{
	SDLWindow sdlWindow;

	sdlWindow.Init();

	sdlWindow.MainLoop();

	return 0;
}