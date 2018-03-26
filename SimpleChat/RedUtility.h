#pragma once
#include <iostream>
#include <string>
#include <sstream>

namespace red {
	void clearConsole();
	void pause(std::wstring msg);
	void pause();
	void writeLine(std::wstring msg, int status);
	void writeLine(std::wstring msg);
	void writeLine(int i);
	int getInt(std::wistream &stream);
}