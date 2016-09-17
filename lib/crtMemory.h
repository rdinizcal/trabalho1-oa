#ifndef CRTMEMORY_H
#define CRTMEMORY_H

#include "memory.h"

#include <iostream>
#include <fstream>
#include <string>

class CrtMemory{

private:
	int avg_seek;
	int min_seek;
	int lat;
	int transfer;

public:
	CrtMemory();

	bool writeMemory(int, Memory*);
	bool readMemory(int,Memory*);
	bool eraseMemory(int, Memory*);
	void showFAT(int,Memory*);

private:
	int mapToPos(sector_map);
	sector_map posToMap(int pos);
	unsigned int findFirstSector(int, std::string, Memory*);
	bool fileExists(int, std::string, Memory*);
	sector_map findEmptyCluster(Memory*);
	sector_map findNextEmptyCluster(Memory*,sector_map);
};

#endif