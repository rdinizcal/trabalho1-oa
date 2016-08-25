#ifndef CRTMEMORY_H
#define CRTMEMORY_H

#include "memory.h"

class CrtMemory{

public:
	CrtMemory();

	void writeMemory(Memory memory);
	void readMemory(Memory memory);
	void eraseMemory(Memory memory);
};

#endif