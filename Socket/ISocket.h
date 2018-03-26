#pragma once

class ISocket {
private:
	int lastError;
public:
	enum {
		SOCKET_VALID,
		RESOLVE_ERROR,
		LISTEN_ERROR,
		BIND_ERROR,
		LISTEN_SOCKET_ERROR,
		ACCEPT_ERROR,
		RESPONSE_ERROR,
		REQUEST_ERROR,
		SHUTDOWN_ERROR,
		SERVER_SOCKET_ERROR,
		SERVER_CONNECTION_ERROR,
		SENDING_ERROR,
		END_TRANSMISSION_ERROR
	};
	int getLastError();
	void setLastError(int error);
};