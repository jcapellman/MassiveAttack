#ifndef __RETURN_SET__
#define __RETURN_SET__

#include "../Main.h"

template <class T> 
class ReturnSet {
public:
	T ReturnValue;

	string ExceptionString() const
	{
		return m_exception.what();
	}

	bool HasError() const
	{
		return m_hasError;
	}

	explicit ReturnSet(exception exception) {
		m_exception = exception;
		m_hasError = true;
	}

	explicit ReturnSet(T objectValue) {
		ReturnValue = objectValue;
		m_hasError = false;
	}
private:
	exception m_exception;
	bool m_hasError;
};
#endif
