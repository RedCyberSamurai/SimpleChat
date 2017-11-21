#pragma once
#include <string>

#include "WindowsSocket.h"

class ServerSocket {
private:
	std::string file;
	WindowsSocket *ws;
	struct addrinfo address, *result;
	SOCKET listener = INVALID_SOCKET;
	SOCKET client = INVALID_SOCKET;
	int lastError;
public:
	enum { SOCKET_VALID, RESOLVE_ERROR, LISTEN_ERROR, BIND_ERROR, LISTEN_SOCKET_ERROR, ACCEPT_ERROR };
	ServerSocket(WindowsSocket &ws);
	int start();
};