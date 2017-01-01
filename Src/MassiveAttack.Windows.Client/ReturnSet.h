#pragma once
#include "Main.h"

template <class T> class ReturnSet<T> {
public:
	T ReturnValue;

	string ExceptionString;

	ReturnSet<T>(T objectValue, string exceptionString) {
		ReturnValue = objectValue;
		ExceptionString = exceptionString;
	}
};