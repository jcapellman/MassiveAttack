#ifndef _SDLWINDOW_
#define _SDLWINDOW_

#include "Main.h"
#include "TextureManager.h"

class SDLWindow
{
public:
	void Init();
	void LoadLevel(char * level);

	void MainLoop();

	SDLWindow()
	{
		this->width = 1024;
		this->height = 768;
	}
private:
	void handle_key_down(SDL_keysym* keysym);
	void process_events(void);

	void InitGL();
	void ResizeWindow();
	void Render();
	void Quit();

	SDL_Surface *surface;

	int width;
	int height;

	TextureManager textureManager;
	int textureID;

	/* Build Our Vertex Structure */
	typedef struct
	{
		float x, y, z; /* 3D Coordinates */
		float u, v;    /* Texture Coordinates */
	} vertex;

	/* Build Our Triangle Structure */
	typedef struct
	{
		vertex vertex[3]; /* Array Of Three Vertices */
	} triangle;

	/* Build Our Sector Structure */
	typedef struct
	{
		int numTriangles;   /* Number Of Triangles In Sector */
		triangle *triangle; /* Pointer To Array Of Triangles */
	} sector;


	sector sector1;     /* Our sector */

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