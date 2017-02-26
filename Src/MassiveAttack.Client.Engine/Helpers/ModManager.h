#ifndef __MOD_MANAGER__
#define __MOD_MANAGER__

#include "../Main.h"

enum ASSET_TYPE
{
	TEXTURES,
	MAPS,
	SOUNDS,
	MUSIC,
	FONTS,
	ROOT
};

const string ROOT_PATH_TEXTURES = "textures";
const string ROOT_PATH_MAPS = "maps";
const string ROOT_PATH_SOUNDS = "sounds";
const string ROOT_PATH_MUSIC = "music";
const string ROOT_PATH_FONTS = "fonts";

#define DEFAULT_MOD "base"

class ModManager
{
	public:
	explicit ModManager(string modName)
		{
			m_modName = modName;
		}

		string GetPath(ASSET_TYPE assetType) const
		{
			return GetPath(assetType, "");
		}

		string GetPath(ASSET_TYPE assetType, string fileName) const
		{
			string assetPath = "";
		
			switch (assetType)
			{
				case SOUNDS:
					assetPath = ROOT_PATH_SOUNDS;
					break;
				case MUSIC:
					assetPath = ROOT_PATH_MUSIC;
					break;
				case FONTS:
					assetPath = ROOT_PATH_FONTS;
					break;
				case MAPS:
					assetPath = ROOT_PATH_MAPS;
					break;
				case TEXTURES:
					assetPath = ROOT_PATH_TEXTURES;
					break;
				case ROOT:
				default: 
					assetPath = "";
			}

			if (fileName == "")
			{
				return m_modName + "/" + assetPath + "/";
			}

			string fullFileName = "";

			if (assetPath == "")
			{
				if (m_modName == DEFAULT_MOD)
				{
					return m_modName + "/" + fileName;
				}

				fullFileName = m_modName + "/" + fileName;

				if (!exists(fullFileName))
				{
					return GetPath(assetType, fileName);
				}

				return fullFileName;
			}

			fullFileName = m_modName + "/" + assetPath + "/" + fileName;

			if (!exists(fullFileName))
			{
				return GetPath(assetType, fileName);
			}

			return fullFileName;
		}
	private:
		static bool exists(string filePath)
		{
			ifstream file(filePath.c_str());
			return file.good();
		}

		string m_modName;
};

#endif
