#pragma once
#include <Winsock2.h>
#include <ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")

class WindowsSocket {
private:
	WSADATA wsaData;
	int socketStatus;
public:
	WindowsSocket();
	bool isSupported();
	int getStatus();
	void terminate();
};