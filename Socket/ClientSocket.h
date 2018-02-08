#pragma once
#include <string>

#include "WindowsSocket.h"

class ClientSocket {
private:
	std::string file;
	PCSTR port = "12345";
	WindowsSocket *ws;
	struct addrinfo address, *result;
	SOCKET server = INVALID_SOCKET;
	int lastError;
public:
	ClientSocket(WindowsSocket &ws);
	enum { SOCKET_VALID, RESOLVE_ERROR, SERVER_SOCKET_ERROR, SERVER_CONNECTION_ERROR, SENDING_ERROR, END_TRANSMISSION_ERROR, SHUTDOWN_ERROR };
	int start();
};