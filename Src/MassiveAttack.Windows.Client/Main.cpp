#include "Main.h"
#include "SDLWindow.h"

static void quit_tutorial(int code)
{
	SDL_Quit();

	exit(code);
}

static void handle_key_down(SDL_keysym* keysym)
{
	switch (keysym->sym) {
		case SDLK_ESCAPE:
			quit_tutorial(0);
			break;
		default:
			break;
	}
}

static void process_events(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {

		switch (event.type) {
		case SDL_KEYDOWN:
			handle_key_down(&event.key.keysym);
			break;
		case SDL_QUIT:
			quit_tutorial(0);
			break;
		}
	}
}

int main(int argc, char *argv[])
{
	SDLWindow sdlWindow;

	sdlWindow.Init();

	while (1) {
		process_events();

		sdlWindow.Render();
	}

	return 0;
}