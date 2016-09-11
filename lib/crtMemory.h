#ifndef CRTMEMORY_H
#define CRTMEMORY_H

#include "memory.h"

class CrtMemory{

public:
	CrtMemory();

	void writeMemory(Memory*);
	void readMemory(Memory*);
	void eraseMemory(Memory*);

private:
	void voidMethodTest(Memory*);
	sector_map findEmptyCluster(Memory*);
	sector_map findNextEmptyCluster(Memory*,sector_map);
};

#endif