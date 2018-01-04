#include "ServerSocket.h"

ServerSocket::ServerSocket(WindowsSocket &ws) : file("./settings/server.cfg") {
	this->ws = &ws;
}

int ServerSocket::start() {
	ZeroMemory(&this->address, sizeof(this->address));
	std::string port = "12345";

	this->address.ai_family = AF_INET;
	this->address.ai_socktype = SOCK_STREAM;
	this->address.ai_protocol = IPPROTO_UDP;

	// resolve address
	int resolveStatus = getaddrinfo(NULL, "12345", &this->address, &this->result);
	if (this->result != 0) {
		this->lastError = resolveStatus;
		printf("Could not resolve server address and port: %d", resolveStatus);
		ws->terminate();
		return RESOLVE_ERROR;
	}

	// create socket listener
	this->listener = socket(this->result->ai_family, this->result->ai_socktype, this->result->ai_protocol);
	if (this->listener == INVALID_SOCKET) {
		this->lastError = WSAGetLastError();
		printf("Could not start the listener: %d", WSAGetLastError());
		freeaddrinfo(result);
		this->ws->terminate();
		return LISTEN_ERROR;
	}

	// bind server
	int bindStatus = bind(this->listener, this->result->ai_addr, (int)this->result->ai_addrlen);
	if (bindStatus == SOCKET_ERROR) {
		this->lastError = WSAGetLastError();
		printf("Could not bind the socket to the given address and port: %d", WSAGetLastError());
		freeaddrinfo(this->result);
		closesocket(this->listener);
		this->ws->terminate();
		return BIND_ERROR;
	}

	// listen socket
	if (listen(this->listener, SOMAXCONN) == SOCKET_ERROR) {
		this->lastError = WSAGetLastError();
		printf("Could not listen to socket connection: %d", WSAGetLastError());
		closesocket(this->listener);
		this->ws->terminate();
		return LISTEN_SOCKET_ERROR;
	}

	// accept client (TODO thread)
	this->client = socket(this->listener, NULL, NULL);
	if (this->client == INVALID_SOCKET) {
		closesocket(this->listener);
		this->ws->terminate();
		return ACCEPT_ERROR;
	}

	return SOCKET_VALID;
}