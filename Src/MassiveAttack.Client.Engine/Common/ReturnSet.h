#pragma once
#include "../Main.h"

template <class T> 
class ReturnSet {
public:
	T ReturnValue;

	string ExceptionString() const
	{
		return _exception.what();
	}

	bool HasError() const
	{
		return _hasError;
	}

	ReturnSet(exception exception) {
		_exception = exception;
		_hasError = true;
	}

	ReturnSet(T objectValue) {
		ReturnValue = objectValue;
		_hasError = false;
	}
private:
	exception _exception;
	bool _hasError;
};