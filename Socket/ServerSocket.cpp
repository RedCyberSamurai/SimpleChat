#include "ServerSocket.h"

ServerSocket::ServerSocket(WindowsSocket &ws) : file("./settings/server.cfg") {
	this->ws = &ws;
}

int ServerSocket::start() {
	ZeroMemory(&this->address, sizeof(this->address));

	this->address.ai_family = AF_INET;
	this->address.ai_socktype = SOCK_STREAM;
	this->address.ai_protocol = IPPROTO_TCP;
	this->address.ai_flags = AI_PASSIVE;

	// resolve address
	int resolveStatus = getaddrinfo(NULL, this->port, &this->address, &this->result);
	if (resolveStatus != 0) {
		this->lastError = resolveStatus;
		printf("Could not resolve server address and port: %d\n", resolveStatus);
		ws->terminate();
		return RESOLVE_ERROR;
	}

	printf("Address resolved.\n");

	// create socket listener
	this->listener = socket(this->result->ai_family, this->result->ai_socktype, this->result->ai_protocol);
	if (this->listener == INVALID_SOCKET) {
		this->lastError = WSAGetLastError();
		printf("Could not start the listener: %d\n", this->lastError);
		freeaddrinfo(result);
		this->ws->terminate();
		return LISTEN_ERROR;
	}

	printf("Listener created.\n");

	// bind server
	int bindStatus = bind(this->listener, this->result->ai_addr, (int)this->result->ai_addrlen);
	if (bindStatus == SOCKET_ERROR) {
		this->lastError = WSAGetLastError();
		printf("Could not bind the socket to the given address and port: %d\n", this->lastError);
		freeaddrinfo(this->result);
		closesocket(this->listener);
		this->ws->terminate();
		return BIND_ERROR;
	}

	printf("Server bound.\n");

	// listen socket
	if (listen(this->listener, SOMAXCONN) == SOCKET_ERROR) {
		this->lastError = WSAGetLastError();
		printf("Could not listen to socket connection: %d\n", this->lastError);
		closesocket(this->listener);
		this->ws->terminate();
		return LISTEN_SOCKET_ERROR;
	}

	printf("Listen socket.\n");

	// accept client (TODO thread)
	this->client = accept(this->listener, NULL, NULL);
	if (this->client == INVALID_SOCKET) {
		closesocket(this->listener);
		this->ws->terminate();
		return ACCEPT_ERROR;
	}

	printf("Client accpeted.\n");

	// recieve/send messages
	const int bufferLength = 512;
	char recieveBuffer[bufferLength];
	int response, request;
	do {
		request = recv(this->client, recieveBuffer, bufferLength, 0);
		if (request > 0) {
			printf("Bytes recieved: %d\n", request);
			printf("Message recieved: %s\n", recieveBuffer);

			response = send(this->client, recieveBuffer, request, 0);
			if (response == SOCKET_ERROR) {
				this->lastError = WSAGetLastError();
				printf("Response failed: %d\n", this->lastError);
				closesocket(this->client);
				this->ws->terminate();

				return RESPONSE_ERROR;
			}

			printf("Bytes sent: %d\n", response);
		}

		if (request == 0) {
			printf("Closing connection.\n");
		}

		if (request == SOCKET_ERROR) {
			this->lastError = WSAGetLastError();
			printf("Request failed: %d\n", this->lastError);
			closesocket(this->client);
			this->ws->terminate();

			return REQUEST_ERROR;
		}
	} while (request > 0);

	printf("Messages recieved/sent.\n");

	// shutdown
	int closeServer = shutdown(this->client, SD_SEND);
	if (closeServer == SOCKET_ERROR) {
		this->lastError = WSAGetLastError();
		printf("Shutdown failed: %d\n", this->lastError);
		closesocket(this->client);
		this->ws->terminate();

		return SHUTDOWN_ERROR;
	}

	printf("Server shutdown.\n");

	closesocket(this->client);
	this->ws->terminate();

	printf("Server closed.\n");
	return SOCKET_VALID;
}