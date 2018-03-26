#pragma once
#include <string>

#include "WindowsSocket.h"
#include "ISocket.h"

class ClientSocket : public ISocket {
private:
	std::string file;
	PCSTR port = "12345";
	struct addrinfo address, *result;
	SOCKET server = INVALID_SOCKET;
public:
	ClientSocket();
	//enum { SOCKET_VALID, RESOLVE_ERROR, SERVER_SOCKET_ERROR, SERVER_CONNECTION_ERROR, SENDING_ERROR, END_TRANSMISSION_ERROR, SHUTDOWN_ERROR };
	int start();
};