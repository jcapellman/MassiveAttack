#include "OGL11Renderer.h"
#include "../TextureManager.h"
#include <unordered_map>

ReturnSet<int> OGL11Renderer::LoadTexture(const char * fileName) {
	TextureManager tm;

	ReturnSet<SDL_Surface*> result = tm.LoadTexture(const_cast<char*>(fileName));

	if (result.HasError())
	{
		return ReturnSet<int>(-1);
	}

	GLuint textureID;

	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexImage2D(GL_TEXTURE_2D, 0, 3, result.ReturnValue->w, result.ReturnValue->h, 0, GL_RGB, GL_UNSIGNED_BYTE, result.ReturnValue->pixels);

	SDL_FreeSurface(result.ReturnValue);

	return ReturnSet<int>(textureID);
}

ReturnSet<bool> OGL11Renderer::Shutdown() {
	glDeleteLists(this->dlID, 1);

	return ReturnSet<bool>(true);
}

ReturnSet<bool> OGL11Renderer::Init(int width, int height) {
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	return ReturnSet<bool>(true);
}

void OGL11Renderer::Render(float xpos, float zpos, float walkbias, float yrot, float xrot) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	GLfloat xtrans = -xpos;
	GLfloat ztrans = -zpos;
	GLfloat ytrans = -walkbias - 0.25f;
	GLfloat sceneroty = 0 - yrot;

	glRotatef(xrot, 1.0f, 0, 0);
	glRotatef(sceneroty, 0, 1.0f, 0);

	glTranslatef(xtrans, 0.0f, ztrans);

	glCallList(dlID);
}

ReturnSet<bool> OGL11Renderer::LoadGeometry(char * fileName) {
	unordered_map<string, int> textures;

	dlID = glGenLists(1);

	glNewList(dlID, GL_COMPILE);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	ifstream input_file(fileName, ios::binary);
	LEVELGEOMETRY * level;

	int size = 0;

	input_file.read((char*)&size, sizeof(size));

	level = new LEVELGEOMETRY[size];

	input_file.read((char*)&level, sizeof(level) * size);

	int textureID;
	ifstream map(fileName);

	for (int x = 0; x < size; x++)
	{
		if (!textures.count(level[x].FileName))
		{
			ReturnSet<int> textureResult = LoadTexture(level[x].FileName);

			if (!textureResult.HasError())
			{
				textureID = textureResult.ReturnValue;
				textures.emplace(level[x].FileName, textureID);
			}
		}
		else
		{
			textureID = textures[level[x].FileName];
		}
	
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glBegin(GL_QUADS);
			glTexCoord2i(0, 0);
			glVertex3f(level[x].X1, level[x].Y1, level[x].Z1);

			glTexCoord2i(0, level[x].Scale);
			glVertex3f(level[x].X2, level[x].Y2, level[x].Z2);

			glTexCoord2i(level[x].Scale, level[x].Scale);
			glVertex3f(level[x].X3, level[x].Y3, level[x].Z3);

			glTexCoord2i(level[x].Scale, 0);
			glVertex3f(level[x].X4, level[x].Y4, level[x].Z4);
		glEnd();
	}

	glEndList();

	return ReturnSet<bool>(true);
}