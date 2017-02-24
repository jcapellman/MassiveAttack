#include "SDLWindow.h"
#include "GfxRenderers/OGL11Renderer.h"
#include "SfxRenderers/SDLRenderer.h"

void SDLWindow::Quit() const
{
	m_gfxRenderer->Shutdown();

	SDL_GL_DeleteContext(m_glcontext);

	SDL_ShowCursor(1);

	SDL_Quit();

	exit(0);
}

void SDLWindow::handle_key_down(SDL_Keysym* keysym)
{
	switch (keysym->sym) {
		case SDLK_ESCAPE:
			Quit();
			break;
		default:
			m_currentGameState->PassKeyEvent(keysym->sym, &m_renderParameters, &m_eventQueue);
			break;
	}

	processEventQueue();
}

void SDLWindow::processEventQueue()
{
	EVENT event;

	do {
		event = m_eventQueue.GetEvent();

		switch (event.EventType)
		{
		case AUDIO_PLAY_SOUND:
			m_sfxRenderer->Play(event.argument);
			break;
		case AUDIO_LOAD_SOUND:
			m_sfxRenderer->Load(event.argument);
		}
	} while (!m_eventQueue.IsEmpty());
}

void SDLWindow::handle_mouse_motion(SDL_MouseMotionEvent* motion)
{
	m_currentGameState->PassMouseEvent(this->_mouseX, motion->x, this->_mouseY, motion->y, &m_renderParameters);
}

void SDLWindow::process_events(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYUP:
		case SDL_KEYDOWN:
			handle_key_down(&event.key.keysym);
			break;
		case SDL_MOUSEMOTION:
			handle_mouse_motion(&event.motion);
			break;
		case SDL_QUIT:
			Quit();
			break;
		default: ;
		}
	}
}

void SDLWindow::MainLoop()
{
	while (true) {
		process_events();

		Render();
	}
}

void SDLWindow::Render() const
{
	static auto T0 = 0;
	static auto Frames = 0;

	m_gfxRenderer->Render(this->m_renderParameters);

	SDL_GL_SwapWindow(m_window);

	Frames++;
	{
		int t = SDL_GetTicks();

		if (t - T0 >= 300) {
			auto seconds = (t - T0) / 1000.0;
			auto fps = Frames / seconds;

			auto caption = this->m_appName + to_string(round(fps)) + " fps";

			T0 = t;
			Frames = 0;
		}
	}
}

void SDLWindow::writeLog(const char * logMessage)
{
	this->m_errorLogger.WriteError(logMessage);
}

void SDLWindow::SetGameState(IGameStates * gameState)
{
	this->m_currentGameState = gameState;

	auto result = m_gfxRenderer->LoadGeometry(this->m_currentGameState->GetGeometry());

	if (result.HasError()) {
		this->writeLog("Failed to set state");
	}
}

void SDLWindow::Init(string appName)
{
	this->m_appName = appName;

	int videoFlags;

	this->m_errorLogger = ErrorLogger();

	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_ShowCursor(0);

	videoFlags = SDL_WINDOW_OPENGL;
	videoFlags |= SDL_GL_DOUBLEBUFFER;
	
	ConfigParser config("base/config.cfg");

	this->width = config.GetInt(CONFIG_XRES);

	this->height = config.GetInt(CONFIG_YRES);

	if (!config.GetBool(CONFIG_FULLSCREEN))
	{
		videoFlags |= SDL_WINDOW_RESIZABLE;
	}

	m_window = SDL_CreateWindow(this->m_appName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->width, this->height, videoFlags);

	m_glcontext = SDL_GL_CreateContext(m_window);

	auto flags = IMG_INIT_JPG | IMG_INIT_PNG;
	IMG_Init(flags);
	TTF_Init();

	m_gfxRenderer = new OGL11Renderer;

	m_gfxRenderer->Init(width, height);

	this->m_renderParameters = RENDER_PARAMETERS();

	this->m_renderParameters.SetParamString(RPARAM_XROT, "0.0f");
	this->m_renderParameters.SetParamString(RPARAM_YROT, "0.0f");
	this->m_renderParameters.SetParamString(RPARAM_XPOS, "1.5f");
	this->m_renderParameters.SetParamString(RPARAM_ZPOS, "6.0f");

	m_sfxRenderer = new SDLRenderer;

	m_sfxRenderer->Init(config.GetInt(CONFIG_AUDIO_NUM_CHANNELS));
}