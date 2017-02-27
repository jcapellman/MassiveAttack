#include "OGL11Renderer.h"
#include "../Managers/TextureManager.h"

GLenum OGL11Renderer::getTextureFormat(Uint8 bpp, Uint32 rmask)
{
	GLenum textureFormat = GL_BGR_EXT;

	if (bpp == 4)	// 32 bit
	{
		if (rmask == 0x000000ff) {
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
		if (rmask == 0x000000ff) {
			textureFormat = GL_RGB;
		}
		else {
			textureFormat = GL_BGR_EXT;
		}
	}

	return textureFormat;
}

ReturnSet<int> OGL11Renderer::LoadTexture(string fileName) {
	auto tm = TextureManager();

	fileName = m_modManager->GetPath(TEXTURES, fileName);

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
	
	glTexImage2D(GL_TEXTURE_2D, 0, result.ReturnValue->format->BytesPerPixel, result.ReturnValue->w, result.ReturnValue->h, 0, getTextureFormat(result.ReturnValue->format->BytesPerPixel, result.ReturnValue->format->Rmask), GL_UNSIGNED_BYTE, result.ReturnValue->pixels);

	SDL_FreeSurface(result.ReturnValue);

	return ReturnSet<int>(textureID);
}

int OGL11Renderer::LoadSkyboxTexture(string fileName)
{
	auto tm = TextureManager();

	fileName = m_modManager->GetPath(SKYBOXES, fileName);

	auto result = tm.LoadTexture(const_cast<char*>(fileName.c_str()));

	if (result.HasError())
	{
		return -1;
	}

	GLuint textureID;

	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, result.ReturnValue->format->BytesPerPixel, result.ReturnValue->w, result.ReturnValue->h, 0, getTextureFormat(result.ReturnValue->format->BytesPerPixel, result.ReturnValue->format->Rmask), GL_UNSIGNED_BYTE, result.ReturnValue->pixels);

	SDL_FreeSurface(result.ReturnValue);

	return textureID;
}

ReturnSet<int> OGL11Renderer::LoadSkybox(string fileName) {
	auto textureID = LoadSkyboxTexture(fileName);

	auto dlID = glGenLists(1);

	this->m_3d_displayLists.push_back(dlID);

	glNewList(dlID, GL_COMPILE);

	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);

	glColor4f(1, 1, 1, 1);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glBegin(GL_QUADS);
		glTexCoord2f(1, 0); glVertex3f(100.0f, 0, 0);
		glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
		glTexCoord2f(0, 1); glVertex3f(0, 6.0f, 0);
		glTexCoord2f(1, 1); glVertex3f(100.0f, 6.0f, 0);
	glEnd();

	glPopAttrib();
	glPopMatrix();

	glEndList();

	return ReturnSet<int>(textureID);
}

void OGL11Renderer::AddUpdateText(string key, string content, string fontName, int x, int y, float size, SDL_Color foregroundColor)
{
	auto result = m_fontManager->RenderText(fontName, content, size, foregroundColor);

	if (result.HasError())
	{
		return;
	}

	auto textSurface = result.ReturnValue;

	auto iterator = m_2d_displayLists.find(key);

	if (iterator != m_2d_displayLists.end())
	{
		m_2d_displayLists.erase(iterator);
	}

	auto dlID = glGenLists(1);

	this->m_2d_displayLists[key] = dlID;

	glNewList(dlID, GL_COMPILE);

	GLuint texture;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ZERO);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA , textSurface->w, textSurface->h, 0, getTextureFormat(textSurface->format->BytesPerPixel, textSurface->format->Rmask), GL_UNSIGNED_BYTE, textSurface->pixels);

	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 0); glVertex2f(x, y);
		glTexCoord2f(1, 0); glVertex2f(x + textSurface->w, y);
		glTexCoord2f(1, 1); glVertex2f(x + textSurface->w, y + textSurface->h);
		glTexCoord2f(0, 1); glVertex2f(x, y + textSurface->h);
	}
	glEnd();

	glDisable(GL_BLEND);

	glEndList();
}

void OGL11Renderer::LoadTextureDefinitions()
{
	ifstream textureDefFile("base/texture.db");

	if (!textureDefFile.good())
	{
		return;
	}

	string fileName;
	int id;

	while (textureDefFile >> id >> fileName)
	{
		_textureDB.emplace(id, fileName);
	}

	textureDefFile.close();
}

ReturnSet<bool> OGL11Renderer::Shutdown() {
	this->ClearRenderQueue();

	return ReturnSet<bool>(true);
}

ReturnSet<bool> OGL11Renderer::Init(int width, int height, ModManager * modManager) {
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

	gluPerspective(45.0f, GLfloat(width) / GLfloat(height), 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	m_modManager = modManager;
	IGfxRenderer::m_fontManager = new FontManager(modManager);

	m_width = width;
	m_height = height;

	return ReturnSet<bool>(true);
}

void OGL11Renderer::Render(RENDER_PARAMETERS rParams) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	
	auto xtrans = rParams.GetParamFloat(RPARAM_XPOS) * -1;
	auto ztrans = rParams.GetParamFloat(RPARAM_ZPOS) * -1;	
	auto sceneroty = 0 - rParams.GetParamFloat(RPARAM_YROT);

	glRotatef(rParams.GetParamFloat(RPARAM_XROT), 1.0f, 0, 0);
	glRotatef(sceneroty, 0, 1.0f, 0);

	glTranslatef(xtrans, 0.0f, ztrans);

	for (unsigned int x = 0; x < this->m_3d_displayLists.size(); x++) 
	{
		glCallList(this->m_3d_displayLists[x]);
	}

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, m_width, m_height, 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();
	glDisable(GL_CULL_FACE);

	glClear(GL_DEPTH_BUFFER_BIT);

	for (auto index : m_2d_displayLists)
	{
		glCallList(this->m_2d_displayLists[index.first]);
	}

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void OGL11Renderer::ClearRenderQueue() {
	// TODO Clear Textures

	for (auto index : m_2d_displayLists)
	{	
		glDeleteLists(this->m_2d_displayLists[index.first], 1);
	}

	for (unsigned int x = 0; x < this->m_3d_displayLists.size(); x++) {
		glDeleteLists(this->m_3d_displayLists[x], 1);
	}
}

ReturnSet<bool> OGL11Renderer::LoadLevel(LEVELGEOMETRY * level) {
	LoadTextureDefinitions();

	unordered_map<int, int> textures;

	auto dlID = glGenLists(1);

	this->m_3d_displayLists.push_back(dlID);
	
	glNewList(dlID, GL_COMPILE);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	int textureID;
	
	for (auto x = 0; x < sizeof(level); x++)
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