#include "RedUtility.h"

// Console input and output utilities
namespace red {
	void pause(const wchar_t *msg) {
		std::wcout << msg << std::endl;
		std::cin.get();
	}

	void pause() {
		pause(L"Press Enter to continue...");
	}

	void writeLine(const wchar_t *msg, int status) {
		std::wcout << msg << status << std::endl;
	}

	void writeLine(const wchar_t *msg) {
		std::wcout << msg << std::endl;
	}

	void writeLine(int i) {
		std::wcout << i << std::endl;
	}

	int getInt(std::istream &stream) {
		int value = -1;

		while (stream) {
			std::string line;
			std::getline(stream, line);

			std::stringstream ss(line);
			if ((ss >> value)) {
				break;
			}

			writeLine(L"Error - Your input has to be a number.");
		}

		return value;
	}
}