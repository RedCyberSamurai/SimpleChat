#include "RedUtility.h"
#include "Endian.h"

#include "Environment.h"

int main()
{
	int envChoice = -1;
	do {
		red::writeLine(L"# Choose your environment:");
		red::writeLine(L"0 Exit");
		red::writeLine(L"1 Client");
		red::writeLine(L"2 Server");

		envChoice = red::getInt(std::cin);
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
		env.createClient(ws);
		break;
	case Environment::Server:
		env.createServer(ws);
		break;
	case Environment::Exit:
	default:
		break;
	}

	red::pause();
    return 0;
}