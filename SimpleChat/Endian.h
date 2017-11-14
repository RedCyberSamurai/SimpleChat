#pragma once

class Endian {
private:
public:
	enum { Little, Big };
	int get();
};