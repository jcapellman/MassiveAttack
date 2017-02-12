#include "OGL11Renderer.h"
#include "../TextureManager.h"

ReturnSet<int> OGL11Renderer::LoadTexture(string fileName) {
	TextureManager tm;

	fileName = TEXTURES_ROOT_PATH + fileName;

	auto result = tm.LoadTexture(const_cast<char*>(fileName.c_str()));

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
	
	GLenum textureFormat = GL_BGR_EXT;

	GLint bpp = result.ReturnValue->format->BytesPerPixel;

	if (bpp == 4)	// 32 bit
	{
		if (result.ReturnValue->format->Rmask == 0x000000ff) {
			textureFormat = GL_RGBA;
		}
		else {
			textureFormat = GL_BGRA_EXT;
		}

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}
	else if (bpp == 3)	// 24 bit
	{
		if (result.ReturnValue->format->Rmask == 0x000000ff) {
			textureFormat = GL_RGB;
		}
		else {
			textureFormat = GL_BGR_EXT;
		}
	}

	glTexImage2D(GL_TEXTURE_2D, 0, bpp, result.ReturnValue->w, result.ReturnValue->h, 0, textureFormat, GL_UNSIGNED_BYTE, result.ReturnValue->pixels);

	SDL_FreeSurface(result.ReturnValue);

	return ReturnSet<int>(textureID);
}

void OGL11Renderer::LoadTextureDefinitions()
{
	ifstream textureDefFile("base/texture.db");

	string fileName;
	int id;

	while (textureDefFile >> id >> fileName)
	{
		_textureDB.emplace(id, fileName);
	}

	textureDefFile.close();
}

ReturnSet<bool> OGL11Renderer::Shutdown() {
	for (int x = 0; x < this->m_displayLists.size(); x++) {
		glDeleteLists(this->m_displayLists[x], 1);
	}

	return ReturnSet<bool>(true);
}

ReturnSet<bool> OGL11Renderer::Init(int width, int height) {
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

void OGL11Renderer::Render(RENDER_PARAMETERS rParams) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glRotatef(rParams.GetParamFloat(RPARAM_XPOS), 1.0f, 0, 0);
	glRotatef(0 - rParams.GetParamFloat(RPARAM_YROT), 0, 1.0f, 0);

	glTranslatef(rParams.GetParamFloat(RPARAM_XPOS), 0.0f, rParams.GetParamFloat(RPARAM_ZPOS));

	for (int x = 0; x < this->m_displayLists.size(); x++) {
		glCallList(this->m_displayLists[x]);
	}
}

ReturnSet<bool> OGL11Renderer::LoadGeometry(LEVELGEOMETRY * level) {
	LoadTextureDefinitions();

	unordered_map<int, int> textures;

	auto dlID = glGenLists(1);

	this->m_displayLists.push_back(dlID);
	
	glNewList(dlID, GL_COMPILE);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	int textureID;
	
	for (int x = 0; x < sizeof(level); x++)
	{
		if (!textures.count(level[x].textureID))
		{
			auto fileName = _textureDB[level[x].textureID];

			auto textureResult = LoadTexture(fileName);

			if (!textureResult.HasError())
			{
				textureID = textureResult.ReturnValue;
				textures.emplace(level[x].textureID, textureID);
			}
		}
		else
		{
			textureID = textures[level[x].textureID];
		}
	
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glColor3f(1.0f, 1.0f, 1.0f);
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