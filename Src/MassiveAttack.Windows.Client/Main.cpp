#include "Main.h"
#include "SDLWindow.h"

int main(int argc, char *argv[])
{
	SDLWindow sdlWindow;

	sdlWindow.Init();

	sdlWindow.MainLoop();

	return 0;
}