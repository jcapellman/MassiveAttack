#include "SDLWindow.h"
#include "GfxRenderers/OGL11Renderer.h"

void SDLWindow::Quit()
{
	_gfxRenderer->Shutdown();

	SDL_ShowCursor(1);

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
		case SDLK_a:
			xpos -= (float)sin(yrot * piover180) * 10.5f;
			zpos += (float)cos(yrot * piover180) * 0.5f;

			if (walkbiasangle >= 359.0f)
				walkbiasangle = 0.0f;
			else
				walkbiasangle += 10;

			walkbias = (float)sin(walkbiasangle * piover180) / 20.0f;
			break;
		case SDLK_d:
			xpos += (float)sin(yrot * piover180) * 10.5f;
			zpos -= (float)cos(yrot * piover180) * 0.5f;

			if (walkbiasangle >= 359.0f)
				walkbiasangle = 0.0f;
			else
				walkbiasangle += 10;

			walkbias = (float)sin(walkbiasangle * piover180) / 20.0f;
			break;
		case SDLK_w:
			xpos -= (float)sin(yrot * piover180) * 0.5f;
			zpos -= (float)cos(yrot * piover180) * 0.5f;

			if (walkbiasangle >= 359.0f)
				walkbiasangle = 0.0f;
			else
				walkbiasangle += 10;

			walkbias = (float)sin(walkbiasangle * piover180) / 20.0f;
			break;
		case SDLK_s:
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

void SDLWindow::handle_mouse_motion(SDL_MouseMotionEvent* motion)
{
	if (motion->x != this->_mouseX)
	{
		if (this->_mouseX > motion->x)
		{
			yrot += 0.5f;
		} else
		{
			yrot -= 0.5f;
		}

		this->_mouseX = motion->x;
	}

	if (motion->y != this->_mouseY)
	{
		if (this->_mouseY > motion->y && xrot > -100)
		{
			xrot -= 0.5f;
		}
		else if (this->_mouseY < motion->y && xrot < 100)
		{
			xrot += 0.5f;
		}

		this->_mouseY = motion->y;
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
		case SDL_MOUSEMOTION:
			handle_mouse_motion(&event.motion);
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

	_gfxRenderer->Render(xpos, zpos, walkbias, yrot, xrot);

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

	SDL_ShowCursor(0);

	info = SDL_GetVideoInfo();

	videoFlags = SDL_OPENGL;
	videoFlags |= SDL_HWSURFACE;
	videoFlags |= SDL_GL_DOUBLEBUFFER;

	surface = SDL_SetVideoMode(this->width, this->height, info->vfmt->BitsPerPixel, videoFlags);

	SDL_WM_ToggleFullScreen(surface);

	_gfxRenderer = new OGL11Renderer;

	_gfxRenderer->Init(width, height);

	/*ReturnSet<SDL_Surface*> floor = textureManager.LoadTexture("wall.bmp");

	if (!floor.HasError()) {
		_gfxRenderer->LoadTexture(floor.ReturnValue);
	}*/

	_gfxRenderer->LoadGeometry("E1M1.map");

	xrot = 0.0f;
	walkbias = 0.0f;
	walkbiasangle = 0.0f;
}