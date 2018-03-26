#pragma once
#include "WindowsSocket.h"
#include "ServerSocket.h"
#include "ClientSocket.h"

class Environment {
private:
public:
	enum { Exit, Client, Server };
	void createServer();
	void createClient();

	void reportStatus(int status, int error);
};