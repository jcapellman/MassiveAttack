#ifndef __ERROR_LOGGER__
#define __ERROR_LOGGER__

#include "Main.h"

#define ERROR_LOGGER_DEFAULT_FILENAME "errors.log"

class ErrorLogger
{
public:
	ErrorLogger() : ErrorLogger(ERROR_LOGGER_DEFAULT_FILENAME) { }

	explicit ErrorLogger(string errorFile)
	{
		m_filename = errorFile;
	}

	void WriteError(string error)
	{
		ofstream file;

		file.open(this->m_filename);

		file << error << endl;

		file.close();
	}
private:
	string m_filename;
};
#endif