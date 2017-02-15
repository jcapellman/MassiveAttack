#include "Level.h"

ReturnSet<LEVELGEOMETRY*> Level::LoadLevel(char* fileName)
{
	try {
		char fullFileName[255];

		strcpy(fullFileName, MAPS_ROOT_PATH.c_str());
		strcat(fullFileName, fileName);

		ifstream input_file(fullFileName);

		if (!input_file.good())
		{
			throw exception(fullFileName);
		}

		LEVELGEOMETRY * level;
		string line;

		input_file >> line;

		level = new LEVELGEOMETRY[atoi(line.c_str())];
		auto idx = 0;

		while (!input_file.eof())
		{
			input_file >> level[idx].textureID >> level[idx].Scale >> level[idx].X1 >> level[idx].Y1 >> level[idx].Z1 >> level[idx].X2 >> level[idx].Y2 >> level[idx].Z2 >> level[idx].X3 >> level[idx].Y3 >> level[idx].Z3 >> level[idx].X4 >> level[idx].Y4 >> level[idx].Z4;

			idx++;
		}

		return ReturnSet<LEVELGEOMETRY*>(level);
	} catch (exception ex)
	{
		return ReturnSet<LEVELGEOMETRY*>(ex);
	}
}
