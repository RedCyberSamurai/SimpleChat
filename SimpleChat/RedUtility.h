#pragma once

#include <iostream>
#include <string>
#include <sstream>

namespace red {
	static void pause();
	static void writeLine(const char* str);
	static void writeLine(int i);
	static int getInt(std::istream &stream);
}