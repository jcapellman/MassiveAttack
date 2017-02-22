#ifndef _SDLWINDOW_
#define _SDLWINDOW_

#include "Main.h"
#include "Common\ReturnSet.h"
#include "Managers\TextureManager.h"
#include "Helpers\Level.h"
#include "GfxRenderers/IGfxRenderer.h"
#include "Config\ConfigParser.h"
#include "Interfaces\IGameStates.h"
#include "Helpers\RenderParameters.h"
#include "Helpers\ErrorLogger.h"
#include "SfxRenderers/ISfxRenderer.h"

class SDLWindow
{
public:
	void Init(string appName);

	void MainLoop();

	void SetGameState(IGameStates * gameState);

	SDLWindow()
	{				
		this->xpos = 1.5f;
		this->zpos = 6.0f;
		this->yrot = 0.0f;
		this->m_glcontext = nullptr;
		this->m_gfxRenderer = nullptr;
		this->m_sfxRenderer = nullptr;
	}
private:	
	IGfxRenderer * m_gfxRenderer;
	ISfxRenderer * m_sfxRenderer;

	IGameStates * m_currentGameState;
	RENDER_PARAMETERS m_renderParameters;
	ErrorLogger m_errorLogger;

	SDL_Window* m_window;
	SDL_GLContext m_glcontext;

	void handle_key_down(SDL_Keysym* keysym);
	void handle_mouse_motion(SDL_MouseMotionEvent* motion);
	void process_events(void);

	void Render() const;
	void Quit() const;

	SDL_Surface *surface;

	int width;
	int height;

	int textureID;

	float heading;
	float xpos;
	float zpos;

	float	yrot;
	float walkbias = 0;
	float walkbiasangle = 0;
	float xrot = 0.0f;
	float	z = 0.0f;

	float _mouseX;
	float _mouseY;

	void writeLog(const char * logMessage);

	string m_appName;
};

#endif