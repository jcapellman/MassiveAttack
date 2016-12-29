#include "SDLWindow.h"

GLuint SDLWindow::LoadLevel(char * level)
{
	GLuint dlID = glGenLists(1);

	glNewList(dlID, GL_COMPILE);
		glColor3f(1.0f, 1.0f, 1.0f);

		glBegin(GL_QUADS);
			glVertex3f(10.0f, 10.0f, 0.0f);
			glVertex3f(-10.0f, 10.0f, 0.0f);
			glVertex3f(-10.0f, -10.0f, 0.0f);
			glVertex3f(10.0f, -10.0f, 0.0f);
		glEnd();

	glEndList();

	return dlID;
}

void SDLWindow::InitGL()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	lookupdown = 0.0f;
	walkbias = 0.0f;
	walkbiasangle = 0.0f;
}

void SDLWindow::Quit()
{
	glDeleteLists(this->dlID, 1);

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
			xpos -= (float)sin(yrot * piover180) * 0.05f;
			zpos -= (float)cos(yrot * piover180) * 0.05f;

			if (walkbiasangle >= 359.0f)
				walkbiasangle = 0.0f;
			else
				walkbiasangle += 10;

			walkbias = (float)sin(walkbiasangle * piover180) / 20.0f;
			break;
		case SDLK_DOWN:
			xpos += (float)sin(yrot * piover180) * 0.05f;

			zpos += (float)cos(yrot * piover180) * 0.05f;
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
	static GLint T0 = 0;
	static GLint Frames = 0;

	GLfloat x_m, y_m, z_m, u_m, v_m;
	GLfloat xtrans = -xpos;
	GLfloat ztrans = -zpos;
	GLfloat ytrans = -walkbias - 0.25f;
	GLfloat sceneroty = 360.0f - yrot;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glRotatef(lookupdown, 1.0f, 0.0f, 0.0f);
	glRotatef(sceneroty, 0.0f, 1.0f, 0.0f);

	glTranslatef(xtrans, ytrans, ztrans);
	
	glTranslatef(-1.5f, 0.0f, -6.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glCallList(dlID);

	SDL_GL_SwapBuffers();

	Frames++;
	{
		GLint t = SDL_GetTicks();

		if (t - T0 >= 300) {
			GLfloat seconds = (t - T0) / 1000.0;
			GLfloat fps = Frames / seconds;

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

	SDL_WM_SetCaption("Massive Attack", "Massive Attack");

	info = SDL_GetVideoInfo();

	videoFlags = SDL_OPENGL;
	videoFlags |= SDL_GL_DOUBLEBUFFER;

	surface = SDL_SetVideoMode(this->width, this->height, info->vfmt->BitsPerPixel, videoFlags);

	InitGL();

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	

	this->dlID = LoadLevel("E1M1.map");
}