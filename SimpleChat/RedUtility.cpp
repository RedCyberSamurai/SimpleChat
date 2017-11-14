#include "RedUtility.h"

// Console input and output utilities
namespace red {
	static void pause() {
		std::cin.get();
	}

	static void writeLine(const char* str) {
		std::cout << str << std::endl;
	}

	static void writeLine(int i) {
		std::cout << i << std::endl;
	}

	static int getInt(std::istream &stream) {
		int value = -1;

		while (stream) {
			std::string line;
			std::getline(stream, line);

			std::stringstream ss(line);
			if ((ss >> value)) {
				break;
			}

			writeLine("Error - Your input has to be a number.");
		}

		return value;
	}
}