#include "ISocket.h"

int ISocket::getLastError()
{
	return this->lastError;
}

void ISocket::setLastError(int error)
{
	this->lastError = error;
}
