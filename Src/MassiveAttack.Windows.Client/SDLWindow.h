#ifndef _SDLWINDOW_
#define _SDLWINDOW_

#include "Main.h"
#include "TextureManager.h"

class SDLWindow
{
public:
	void Init();
	GLuint LoadLevel(char * level);

	void MainLoop();

	SDLWindow()
	{
		this->width = 1024;
		this->height = 768;

		this->xpos = 1.5f;
		this->zpos = 6.0f;
	}
private:
	void handle_key_down(SDL_keysym* keysym);
	void process_events(void);

	void InitGL();
	void Render();
	void Quit();

	SDL_Surface *surface;

	GLuint dlID;

	int width;
	int height;

	TextureManager textureManager;
	int textureID;

	const float piover180 = 0.0174532925f;
	float heading;
	float xpos;
	float zpos;

	GLfloat	yrot;
	GLfloat walkbias = 0;
	GLfloat walkbiasangle = 0;
	GLfloat lookupdown = 0.0f;
	GLfloat	z = 0.0f;
};

#endif