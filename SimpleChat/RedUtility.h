#pragma once
#include <iostream>
#include <string>
#include <sstream>

namespace red {
	void pause(const wchar_t *msg);
	void pause();
	void writeLine(const wchar_t *msg, int status);
	void writeLine(const wchar_t *msg);
	void writeLine(int i);
	int getInt(std::istream &stream);
}