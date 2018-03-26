#include "RedUtility.h"

// Console input and output utilities
namespace red {
	std::wostream &console = std::wcout;

	void clearConsole() {
		system("cls");
	}

	void pause(std::wstring msg) {
		console << msg << std::endl;
		std::cin.get();
	}

	void pause() {
		pause(L"Press Enter to continue...");
	}

	void writeLine(std::wstring msg, int status) {
		console << msg << status << std::endl;
	}

	void writeLine(std::wstring msg) {
		console << msg << std::endl;
	}

	void writeLine(int i) {
		console << i << std::endl;
	}

	int getInt(std::wistream &stream) {
		std::wstring line;
		std::getline(stream, line);

		return std::stoi(line);
	}
}