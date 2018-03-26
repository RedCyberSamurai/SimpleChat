#include "Environment.h"

void Environment::createServer() {
	ServerSocket ss;
	int status = ss.start();
	if (status != ServerSocket::SOCKET_VALID) {
		this->reportStatus(status, ss.getLastError());
	}
}

void Environment::createClient()
{
	ClientSocket cs;
	int status = cs.start();
	if (status != ClientSocket::SOCKET_VALID) {
		this->reportStatus(status, cs.getLastError());
	}
}

void Environment::reportStatus(int status, int error)
{
	switch (status) {
	case ISocket::SOCKET_VALID:
		break;
	case ISocket::RESOLVE_ERROR:
		printf("Could not resolve server address and port: %d", error);
		break;
	case ISocket::LISTEN_ERROR:
		printf("Could not start the listener: %d\n", error);
		break;
	case ISocket::BIND_ERROR:
		printf("Could not bind the socket to the given address and port: %d\n", error);
		break;
	case ISocket::LISTEN_SOCKET_ERROR:
		printf("Could not listen to socket connection: %d\n", error);
		break;
	case ISocket::ACCEPT_ERROR:
		printf("Accepting client error: %d\n", error);
		break;
	case ISocket::RESPONSE_ERROR:
		printf("Response failed: %d\n", error);
		break;
	case ISocket::REQUEST_ERROR:
		printf("Request failed: %d\n", error);
		break;
	case ISocket::SHUTDOWN_ERROR:
		printf("Shutdown failed: %d\n", error);
		break;
	case ISocket::SERVER_SOCKET_ERROR:
		printf("Could not create the server socket: %ld\n", error);
		break;
	case ISocket::SERVER_CONNECTION_ERROR:
		printf("Unable to connect to server!\n");
		break;
	case ISocket::SENDING_ERROR:
		printf("Sending message failed: %d\n", error);
		break;
	case ISocket::END_TRANSMISSION_ERROR:
		printf("Could not close connection: %d\n", error);
		break;
	}
}