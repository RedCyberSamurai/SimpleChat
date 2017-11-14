#include "Environment.h"

void Environment::createServer(WindowsSocket &ws) {
	ServerSocket ss(ws);
	ss.start();
}

void Environment::createClient(WindowsSocket &ws)
{
	// TODO
}
