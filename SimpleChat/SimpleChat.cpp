#include <iostream>
#include <string>
#include <sstream>

#include "RedUtility.h"
#include "Endian.h"
#include "WindowsSocket.h"
#include "ServerSocket.h"

enum Environment {
	Exit,
	Client,
	Server
};

//class Client {
//private:
//	struct socketaddr socketData;
//};

int main()
{
	int env = -1;
	do {
		red::writeLine("# Choose your environment:");
		red::writeLine("0 Exit");
		red::writeLine("1 Client");
		red::writeLine("2 Server");

		env = red::getInt(std::cin);
		

	} while (env < 0);

	switch (env) {
	case Environment::Exit:
		break;
	case Environment::Client:
		break;
	case Environment::Server:
		break;
	default:
		break;
	}

	WindowsSocket ws;
	if (!ws.isSupported()) {
		red::writeLine("Windows socket not supported: " + ws.getStatus());
		std::cin.get();
		return 1;
	}

	ServerSocket ss(ws);
	ss.start();

	red::pause();

    return 0;
}