#ifndef MEMORY_H
#define MEMORY_H

#include "../lib/estrutura.h"

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
	void selectMemory();
	void deleteMemory();
	void showFAT();


	void setFat_id(fatlist id);
	fatlist getFat_id();
	void setSector_ent(fatent sec_ent, int pos);
	fatent getSector_ent(int pos);

	void printAttribute();
	
};

#endif