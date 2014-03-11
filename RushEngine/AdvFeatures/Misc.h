#pragma once
#include <sstream>

template <class T>

string ToString(T Input)
{
	stringstream ss;
	string Out;
	ss << Input;
	ss >> Out;
	return Out;
}