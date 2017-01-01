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
		return this->_exception.what() == NULL;
	}

	ReturnSet(exception exception) {
		_exception = exception;
	}

	ReturnSet(T objectValue) {
		ReturnValue = objectValue;
	}
private:
	exception _exception;
};