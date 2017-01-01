#include "SDLWindow.h"
#include "OGL11Renderer.h"

void SDLWindow::Quit()
{
	_gfxRenderer->Shutdown();

	SDL_Quit();

	exit(0);
}

void SDLWindow::handle_key_down(SDL_keysym* keysym)
{
	switch (keysym->sym) {
		case SDLK_ESCAPE:
			Quit();
			break;
		case SDLK_RIGHT:
			yrot -= 1.5f;
			break;
		case SDLK_LEFT:
			yrot += 1.5f;
			break;
		case SDLK_UP:
			xpos -= (float)sin(yrot * piover180) * 0.5f;
			zpos -= (float)cos(yrot * piover180) * 0.5f;

			if (walkbiasangle >= 359.0f)
				walkbiasangle = 0.0f;
			else
				walkbiasangle += 10;

			walkbias = (float)sin(walkbiasangle * piover180) / 20.0f;
			break;
		case SDLK_DOWN:
			xpos += (float)sin(yrot * piover180) * 0.5f;
			zpos += (float)cos(yrot * piover180) * 0.5f;

			if (walkbiasangle <= 1.0f)
				walkbiasangle = 359.0f;
			else
				walkbiasangle -= 10;

			walkbias = (float)sin(walkbiasangle * piover180) / 20.0f;
			break;
		default:
			break;
	}
}

void SDLWindow::process_events(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {

		switch (event.type) {
		case SDL_KEYDOWN:
			handle_key_down(&event.key.keysym);
			break;
		case SDL_QUIT:
			Quit();
			break;
		}
	}
}

void SDLWindow::MainLoop()
{
	while (1) {
		process_events();

		Render();
	}
}

void SDLWindow::Render()
{
	static int T0 = 0;
	static int Frames = 0;

	_gfxRenderer->Render(xpos, zpos, walkbias, yrot);

	SDL_GL_SwapBuffers();

	Frames++;
	{
		int t = SDL_GetTicks();

		if (t - T0 >= 300) {
			double seconds = (t - T0) / 1000.0;
			double fps = Frames / seconds;

			string caption;

			caption = "Massive Attack - " + to_string(round(fps)) + " fps";

			SDL_WM_SetCaption(caption.c_str(), "Massive Attack");

			T0 = t;
			Frames = 0;
		}
	}
}

void SDLWindow::Init()
{
	const SDL_VideoInfo* info = nullptr;

	int videoFlags;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

	SDL_WM_SetCaption("Massive Attack", "Massive Attack");

	info = SDL_GetVideoInfo();

	videoFlags = SDL_OPENGL;
	videoFlags |= SDL_GL_DOUBLEBUFFER;

	surface = SDL_SetVideoMode(this->width, this->height, info->vfmt->BitsPerPixel, videoFlags);

	SDL_WM_ToggleFullScreen(surface);

	_gfxRenderer = new OGL11Renderer;

	_gfxRenderer->Init(width, height);

	_gfxRenderer->LoadGeometry("E1M1.map");

	lookupdown = 0.0f;
	walkbias = 0.0f;
	walkbiasangle = 0.0f;
}