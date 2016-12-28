#include "SDLWindow.h"

void readstr(FILE *f, char *string)
{
	do
	{
		fgets(string, 255, f);
	} while ((string[0] == '/') || (string[0] == '\n'));
	return;
}

void SDLWindow::LoadLevel(char * level)
{
	FILE *filein;        /* File To Work With */

	int numTriangles;    /* Number of Triangles */
	char oneLine[255];   /* One line from conf file */

	float x, y, z, u, v; /* 3d and texture coordinates */

	int triLoop;         /* Triangle loop variable */
	int verLoop;         /* Vertex loop variable */

						 /* Open Our File */
	filein = fopen(level, "rt");

	/* Grab a line from 'filein' */
	readstr(filein, oneLine);

	/* Read in number of triangle */
	sscanf(oneLine, "NUMPOLLIES %d\n", &numTriangles);

	/* allocate space for our triangles */
	//sector1.triangle = malloc(numTriangles * sizeof(triangle));
	
	if (sector1.triangle == NULL)
	{
		fprintf(stderr, "Could not allocate memory for triangles.\n");
		Quit();
	}

	sector1.numTriangles = numTriangles;

	/* Get coords for each triangle */
	for (triLoop = 0; triLoop < numTriangles; triLoop++)
	{
		for (verLoop = 0; verLoop < 3; verLoop++)
		{
			readstr(filein, oneLine);
			sscanf(oneLine, "%f %f %f %f %f\n", &x, &y, &z, &u, &v);
			sector1.triangle[triLoop].vertex[verLoop].x = x;
			sector1.triangle[triLoop].vertex[verLoop].y = y;
			sector1.triangle[triLoop].vertex[verLoop].z = z;
			sector1.triangle[triLoop].vertex[verLoop].u = u;
			sector1.triangle[triLoop].vertex[verLoop].v = v;
		}
	}

	/* Close Our File */
	fclose(filein);
	return;
}

void SDLWindow::InitGL()
{
	GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	/* Diffuse Light Values */
	GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	/* Light Position */
	GLfloat LightPosition[] = { 0.0f, 0.0f, 2.0f, 1.0f };

	glEnable(GL_TEXTURE_2D);

	/* Enable smooth shading */
	glShadeModel(GL_SMOOTH);

	/* Set the background black */
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	/* Depth buffer setup */
	glClearDepth(1.0f);

	/* Enables Depth Testing */
	glEnable(GL_DEPTH_TEST);

	/* The Type Of Depth Test To Do */
	glDepthFunc(GL_LEQUAL);

	/* Really Nice Perspective Calculations */
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	/* Setup The Ambient Light */
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);

	/* Setup The Diffuse Light */
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);

	/* Position The Light */
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);

	/* Enable Light One */
	glEnable(GL_LIGHT1);

	lookupdown = 0.0f;
	walkbias = 0.0f;
	walkbiasangle = 0.0f;

	/* Full Brightness, 50% Alpha */
	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);

	/* Blending Function For Translucency Based On Source Alpha Value */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	//textureID = textureManager.LoadTexture("/base/Textures/Wall/greybrick.bmp");
}

void SDLWindow::Quit()
{
	SDL_Quit();

	/* Deallocate things we allocated */
	if (sector1.triangle)
		free(sector1.triangle);

	/* and exit appropriately */
	exit(0);
}

void SDLWindow::handle_key_down(SDL_keysym* keysym)
{
	switch (keysym->sym) {
	case SDLK_ESCAPE:
		Quit();
		break;
	case SDLK_RIGHT:
		/* Right arrow key was pressed
		* this effectively turns the camera right, but does it by
		* rotating the scene left
		*/
		yrot -= 1.5f;
		break;
	case SDLK_LEFT:
		/* Left arrow key was pressed
		* this effectively turns the camera left, but does it by
		* rotating the scene right
		*/
		yrot += 1.5f;
		break;
	case SDLK_UP:
		/* Up arrow key was pressed
		* this moves the player forward
		*/
		/* Move On The X-Plane Based On Player Direction */
		xpos -= (float)sin(yrot * piover180) * 0.05f;
		/* Move On The Z-Plane Based On Player Direction */
		zpos -= (float)cos(yrot * piover180) * 0.05f;
		if (walkbiasangle >= 359.0f)
			walkbiasangle = 0.0f;
		else
			walkbiasangle += 10;

		/* Causes the player to bounce */
		walkbias = (float)sin(walkbiasangle * piover180) / 20.0f;
		break;
	case SDLK_DOWN:
		/* Down arrow key was pressed
		* this causes the player to move backwards
		*/
		/* Move On The X-Plane Based On Player Direction */
		xpos += (float)sin(yrot * piover180) * 0.05f;
		/* Move On The Z-Plane Based On Player Direction */
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

	/* Floating Point For Temp X, Y, Z, U And V Vertices */
	GLfloat x_m, y_m, z_m, u_m, v_m;
	/* Used For Player Translation On The X Axis */
	GLfloat xtrans = -xpos;
	/* Used For Player Translation On The Z Axis */
	GLfloat ztrans = -zpos;
	/* Used For Bouncing Motion Up And Down */
	GLfloat ytrans = -walkbias - 0.25f;
	/* 360 Degree Angle For Player Direction */
	GLfloat sceneroty = 360.0f - yrot;

	/* Loop variable */
	int loop_m;

	/* Clear The Screen And The Depth Buffer */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	/* Rotate Up And Down To Look Up And Down */
	glRotatef(lookupdown, 1.0f, 0.0f, 0.0f);
	/* Rotate Depending On Direction Player Is Facing */
	glRotatef(sceneroty, 0.0f, 1.0f, 0.0f);

	/* Translate The Scene Based On Player Position */
	glTranslatef(xtrans, ytrans, ztrans);
//	glBindTexture(GL_TEXTURE_2D, textureID);

	glBegin(GL_QUADS);
		glColor3f(1, 0, 0); glVertex3f(0, 0, 0);
		glColor3f(1, 1, 0); glVertex3f(100, 0, 0);
		glColor3f(1, 0, 1); glVertex3f(100, 100, 0);
		glColor3f(1, 1, 1); glVertex3f(0, 100, 0);
	glEnd();

	/* Draw it to the screen */
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

void SDLWindow::ResizeWindow()
{
	GLfloat ratio;

	/* Protect against a divide by zero */
	if (height == 0)
		height = 1;

	ratio = (GLfloat)width / (GLfloat)height;

	/* Setup our viewport. */
	glViewport(0, 0, (GLint)width, (GLint)height);

	/* change to the projection matrix and set our viewing volume. */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/* Set our perspective */
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	/* Make sure we're chaning the model view and not the projection */
	glMatrixMode(GL_MODELVIEW);

	/* Reset The View */
	glLoadIdentity();
}

void SDLWindow::Init()
{
	const SDL_VideoInfo* info = NULL;

	int videoFlags;

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

	surface = SDL_SetVideoMode(this->width, this->height, info->vfmt->BitsPerPixel, videoFlags);

	InitGL();

	ResizeWindow();

	//LoadLevel("E1M1.map");
}