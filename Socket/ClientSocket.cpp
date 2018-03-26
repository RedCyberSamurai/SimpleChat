#include "ClientSocket.h"

ClientSocket::ClientSocket() : file("./settings/client.cfg") {
}

int ClientSocket::start()
{
	ZeroMemory(&this->address, sizeof(this->address));
	this->address.ai_family = AF_UNSPEC;
	this->address.ai_socktype = SOCK_STREAM;
	this->address.ai_protocol = IPPROTO_TCP;

	int resolveStatus = getaddrinfo("127.0.0.1", this->port, &this->address, &this->result);
	if (resolveStatus != 0) {
		this->setLastError(resolveStatus);

		return RESOLVE_ERROR;
	}

	this->server = socket(this->result->ai_family, this->result->ai_socktype, this->result->ai_protocol);
	if (this->server == INVALID_SOCKET) {
		this->setLastError(WSAGetLastError());
		freeaddrinfo(this->result);

		return SERVER_SOCKET_ERROR;
	}

	int connectionStatus = connect(this->server, this->result->ai_addr, (int)this->result->ai_addrlen);
	if (connectionStatus == SOCKET_ERROR) {
		closesocket(this->server);
		this->server = INVALID_SOCKET;
	}

	freeaddrinfo(this->result);
	if (this->server == INVALID_SOCKET) {
		return SERVER_CONNECTION_ERROR;
	}

	const char *testMessage = "Some test message...";

	int sendStatus = send(this->server, testMessage, (int)strlen(testMessage), 0);
	if (sendStatus == SOCKET_ERROR) {
		this->setLastError(WSAGetLastError());
		closesocket(this->server);

		return SENDING_ERROR;
	}

	printf("Bytes sent: %d\n", sendStatus);

	int endTransmission = shutdown(this->server, SD_SEND);
	if (endTransmission == SOCKET_ERROR) {
		this->setLastError(WSAGetLastError());

		return END_TRANSMISSION_ERROR;
	}


	int response;
	const int bufferLength = 512;
	char recieveBuffer[bufferLength];

	do {
		response = recv(this->server, recieveBuffer, bufferLength, 0);
		if (response > 0) {
			printf("Bytes recieved: %d\n", response);
		}

		if (response == 0) {
			printf("Connection closed\n");
		}

		if (response == SOCKET_ERROR) {
			this->setLastError(WSAGetLastError());
			printf("Recieve failed: %d\n", this->getLastError());
		}
	} while (response > 0);

	int closeConnection = shutdown(this->server, SD_SEND);
	if (closeConnection == SOCKET_ERROR) {
		this->setLastError(WSAGetLastError());
		closesocket(this->server);

		return SHUTDOWN_ERROR;
	}

	closesocket(this->server);
	return SOCKET_VALID;
}