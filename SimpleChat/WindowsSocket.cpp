#include "WindowsSocket.h"

WindowsSocket::WindowsSocket() {
	this->socketStatus = WSAStartup(MAKEWORD(2, 2), &this->wsaData);
}

bool WindowsSocket::isSupported() {
	if (this->socketStatus != 0) {
		return false;
	}

	return true;
}

int WindowsSocket::getStatus() {
	return this->socketStatus;
}

void WindowsSocket::terminate() {
	WSACleanup();
}