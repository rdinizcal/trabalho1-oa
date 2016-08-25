#ifndef MEMORY_H
#define MEMORY_H

#include "../lib/estrutura.h"

class Memory{
private:
	track_array *cylinder;
	fatlist *fat_id;
	fatent *sector_ent;
	
public:
	Memory();
	~Memory();
	void insertMemory(unsigned char*, int);
	void selectMemory();
	void deleteMemory();
	void showFAT();

	track_array* getCylinder();
	
private:
	int findEmptyCluster(int , int);
};

#endif