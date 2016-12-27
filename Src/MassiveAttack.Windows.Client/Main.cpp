#include "Main.h"

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

static int setup_opengl()
{
	glShadeModel(GL_SMOOTH);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	return(TRUE);
}

int DrawGLScene(GLvoid)
{
	static GLint T0 = 0;
	static GLint Frames = 0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(-1.5f, 0.0f, -6.0f);

	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();

	glTranslatef(3.0f, 0.0f, 0.0f);

	glColor3f(0.5f, 0.5f, 1.0f);

	glBegin(GL_QUADS);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();

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

	return(TRUE);
}

int resizeWindow(int width, int height)
{
	GLfloat ratio;

	if (height == 0)
		height = 1;

	ratio = (GLfloat)width / (GLfloat)height;

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	return(TRUE);
}

int main(int argc, char *argv[])
{
	const SDL_VideoInfo* info = NULL;

	int videoFlags;
	SDL_Surface *surface;

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_WM_SetCaption("Massive Attack", "Massive Attack");

	info = SDL_GetVideoInfo();

	videoFlags = SDL_OPENGL;
	videoFlags |= SDL_GL_DOUBLEBUFFER;
	videoFlags |= SDL_HWPALETTE;
	videoFlags |= SDL_RESIZABLE;
	videoFlags |= SDL_HWSURFACE;
	videoFlags |= SDL_HWACCEL;

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	surface = SDL_SetVideoMode(800, 600, info->vfmt->BitsPerPixel, videoFlags);

	resizeWindow(800, 600);

	setup_opengl();

	while (1) {
		process_events();

		DrawGLScene();
	}

	return 0;
}