#pragma once
#include "Main.h"

template <class T> 
class ReturnSet {
public:
	T ReturnValue;

	string ExceptionString;

	bool HasError() {
		return !ExceptionString.empty();
	}

	ReturnSet(T objectValue, string exceptionString = "") {
		ReturnValue = objectValue;
		ExceptionString = exceptionString;
	}
};