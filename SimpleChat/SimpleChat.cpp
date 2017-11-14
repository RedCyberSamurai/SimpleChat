#include "RedUtility.h"
#include "Endian.h"

#include "Environment.h"

int main()
{
	int envChoice = -1;
	do {
		red::writeLine("# Choose your environment:");
		red::writeLine("0 Exit");
		red::writeLine("1 Client");
		red::writeLine("2 Server");

		envChoice = red::getInt(std::cin);
	} while (envChoice < 0);

	Environment env;

	WindowsSocket ws;
	if (!ws.isSupported()) {
		red::writeLine("Windows socket not supported: " + ws.getStatus());

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