#pragma once
#include <iostream>
#include <string>
#include <sstream>

namespace red {
	void pause();
	void writeLine(const char* str);
	void writeLine(int i);
	int getInt(std::istream &stream);
}