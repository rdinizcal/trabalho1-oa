#ifndef MEMORY_H
#define MEMORY_H

#include "../lib/estrutura.h"

#include <string>
#include <iostream>

class Memory{
private:
	track_array* cylinder;
	fatlist* fat_id;
	fatent* sector_ent;

	int fileIndex;
	
public:
	Memory();
	~Memory();
	void insertMemory(unsigned char*,sector_map);
	void selectMemory(unsigned char*,sector_map);
	void deleteMemory(std::string, int);

	void setFat_id(fatlist);
	fatlist getFat_id(int);
	void setSector_ent(fatent, int);
	fatent getSector_ent(int);
	
};

#endif