#include "ServerSocket.h"

ServerSocket::ServerSocket(WindowsSocket &ws) : file("./settings/server.cfg") {
	this->ws = &ws;
}

int ServerSocket::start() {
	ZeroMemory(&address, sizeof(address));
	std::string port = "12345";

	address.ai_family = AF_INET;
	address.ai_socktype = SOCK_STREAM;
	address.ai_protocol = IPPROTO_UDP;

	// resolve address
	int resolveStatus = getaddrinfo(NULL, "12345", &address, &result);
	if (result != 0) {
		this->lastError = resolveStatus;
		printf("Could not resolve server address and port: %d", resolveStatus);
		ws->terminate();
		return RESOLVE_ERROR;
	}

	// create socket listener
	listener = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (listener == INVALID_SOCKET) {
		this->lastError = WSAGetLastError();
		printf("Could not start the listener: %d", WSAGetLastError());
		freeaddrinfo(result);
		ws->terminate();
		return LISTEN_ERROR;
	}

	// bind server
	int bindStatus = bind(listener, result->ai_addr, (int)result->ai_addrlen);
	if (bindStatus == SOCKET_ERROR) {
		this->lastError = WSAGetLastError();
		printf("Could not bind the socket to the given address and port: %d", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(listener);
		ws->terminate();
		return BIND_ERROR;
	}

	// listen socket
	if (listen(listener, SOMAXCONN) == SOCKET_ERROR) {
		this->lastError = WSAGetLastError();
		printf("Could not listen to socket connection: %d", WSAGetLastError());
		closesocket(listener);
		ws->terminate();
		return LISTEN_SOCKET_ERROR;
	}

	// accept client (TODO thread)
	client = socket(listener, NULL, NULL);
	if (client == INVALID_SOCKET) {
		closesocket(listener);
		ws->terminate();
		return ACCEPT_ERROR;
	}

	return SOCKET_VALID;
}