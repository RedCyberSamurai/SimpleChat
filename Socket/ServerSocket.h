#pragma once
#include <string>

#include "WindowsSocket.h"
#include "ISocket.h"

class ServerSocket : public ISocket {
private:
	std::string file;
	PCSTR port = "12345";
	struct addrinfo address, *result;
	SOCKET listener = INVALID_SOCKET;
	SOCKET client = INVALID_SOCKET;
public:
	//enum { SOCKET_VALID, RESOLVE_ERROR, LISTEN_ERROR, BIND_ERROR, LISTEN_SOCKET_ERROR, ACCEPT_ERROR, RESPONSE_ERROR, REQUEST_ERROR, SHUTDOWN_ERROR };
	ServerSocket();
	int start();
};