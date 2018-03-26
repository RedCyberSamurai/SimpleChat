#include "RedUtility.h"

#include "Environment.h"

int main()
{
	int envChoice = -1;
	do {
		red::writeLine(L"# Choose your environment:");
		red::writeLine(L"0 Exit");
		red::writeLine(L"1 Client");
		red::writeLine(L"2 Server");

		try {
			envChoice = red::getInt(std::wcin);
		}
		catch (std::exception e) {
			red::clearConsole();
			red::writeLine(L"Error - Your input has to be a number.");
		}
	} while (envChoice < 0);

	Environment env;
	WindowsSocket ws;

	if (!ws.isSupported()) {
		red::writeLine(L"Windows socket not supported: ", ws.getStatus());

		red::pause();
		return 1;
	}

	switch (envChoice) {
	case Environment::Client:
		env.createClient();
		break;
	case Environment::Server:
		env.createServer();
		break;
	case Environment::Exit:
	default:
		break;
	}

	ws.terminate();

	red::pause(L"Exit program...");
    return 0;
}