#include <iostream>
#include <string>
#include <sstream>

#include <Winsock2.h>
#include <ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")

static void pause() {
	std::string s;
	getline(std::cin, s);
}

static void writeLine(const char* str) {
	std::cout << str << std::endl;
}

static void writeLine(int i) {
	std::cout << i << std::endl;
}

static int getInt(std::istream &stream) {
	int value = -1;

	while (stream) {
		std::string line;
		std::getline(stream, line);

		std::stringstream ss(line);
		if ((ss >> value)) {
			break;
		}

		writeLine("Error - Your input has to be a number.");
	}

	return value;
}

class WindowsSocket{
private:
	WSADATA wsaData;
	int socketStatus;
public:
	WindowsSocket() {
		this->socketStatus = WSAStartup(MAKEWORD(2, 2), &this->wsaData);
	}

	bool isSupported() {
		if (this->socketStatus != 0) {
			return false;
		}

		return true;
	}

	int getStatus() {
		return this->socketStatus;
	}

	void terminate() {
		WSACleanup();
	}
};

enum Environment {
	Exit,
	Client,
	Server
};

class Endian {
private:
	
public:
	enum {
		Little,
		Big
	};
	int get() {
		// big endian prefers the smallest address of byte order
		int endianType = Big;

		int var = 0x12345678;
		unsigned char *chr = (unsigned char*)(&var);

		// little endian prefers the biggest address of byte order
		if (*chr == 78) {
			endianType = Little;
		}

		return endianType;
	}
};

//class Client {
//private:
//	struct socketaddr socketData;
//};

class ServerSocket {
private:
	std::string file;
	WindowsSocket *ws;
	struct addrinfo address, *result;
	SOCKET listener = INVALID_SOCKET;
	SOCKET client = INVALID_SOCKET;
	int lastError;
public:
	enum { SOCKET_VALID, RESOLVE_ERROR, LISTEN_ERROR, BIND_ERROR, LISTEN_SOCKET_ERROR, ACCEPT_ERROR };
	ServerSocket(WindowsSocket &ws) : file("./settings/server.cfg") {
		this->ws = &ws;
	}
	int start() {
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
};

int main()
{
	int env = -1;
	do {
		writeLine("# Choose your environment:");
		writeLine("0 Exit");
		writeLine("1 Client");
		writeLine("2 Server");

		env = getInt(std::cin);
		

	} while (env < 0);

	switch (env) {
	case Environment::Exit:
		break;
	case Environment::Client:
		break;
	case Environment::Server:
		break;
	default:
		break;
	}

	WindowsSocket ws;
	if (!ws.isSupported()) {
		writeLine("Windows socket not supported: " + ws.getStatus());
		std::cin.get();
		return 1;
	}

	ServerSocket ss(ws);
	ss.start();

	pause();

    return 0;
}