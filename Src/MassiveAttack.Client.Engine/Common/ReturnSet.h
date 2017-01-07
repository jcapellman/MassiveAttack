#pragma once
#include "../Main.h"

template <class T> 
class ReturnSet {
public:
	T ReturnValue;

	string ExceptionString() {
		return _exception.what();
	}

	bool HasError() {
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