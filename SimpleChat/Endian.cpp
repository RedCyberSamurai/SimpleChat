#include "Endian.h"

int Endian::get() {
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