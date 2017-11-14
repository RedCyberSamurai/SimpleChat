#pragma once
#include "WindowsSocket.h"
#include "ServerSocket.h"
#include "ClientSocket.h"

class Environment {
private:
public:
	enum { Exit, Client, Server };
	void createServer(WindowsSocket &ws);
	void createClient(WindowsSocket &ws);
};