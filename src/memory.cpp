#include "../lib/memory.h"

#include <iostream>

#define MAXCYLINDER 10
#define MAXSECTOR 3000

/**************************CONSTRUTOR**************************/
Memory::Memory(){
	cylinder = new track_array[MAXCYLINDER];
	fat_id = new fatlist[MAXSECTOR];
	sector_ent = new fatent[MAXSECTOR];

	fileIndex=0;

	std::cout<<"Objeto de memoria criado."<<std::endl;
}

/**************************DESTRUTOR**************************/
Memory::~Memory(){
	delete[] cylinder;
	delete[] fat_id;
	delete[] sector_ent;

	std::cout<<"Objeto de memoria destruido."<<std::endl;
}


/**************************METODOS PUBLICOS**************************/
void Memory::insertMemory(unsigned char buffer[], sector_map map){


	std::cout<<"Inserindo cluster na memoria..."<<std::endl;

	/*for(int i=0; i<2048; i++) std::cout<<buffer[i];

	std::cout<<std::endl<<"Done printing buffer.."<<std::endl;
	*/


	std::cout<<"Cylinder: "<<map.cylinder<<" Track: "<<map.track<<" Sector: "<<map.sector<<std::endl;

	for(int i=0; i<4; i++){
		for(int j=0; j<512; j++){
			cylinder[map.cylinder].track[map.track].sector[map.sector].bytes_s[j] = buffer[j+(512*i)];
		}
	}

}

void Memory::selectMemory(){

}

void Memory::deleteMemory(){

}

void Memory::showFAT(){

}

void Memory::printAttribute(){

	std::cout<<"Printing fatent"<<std::endl;
	for(int i=0; i<3000; i++){
		std::cout<<i<<"- used: "<<sector_ent[i].used<<" eof: "<<sector_ent[i].eof<<" next: "<<sector_ent[i].next<<std::endl;
	}
	
}

/**************************SETTERS & GETTERS**************************/
void Memory::setFat_id(fatlist id){
	fat_id[fileIndex++]=id;
}

fatlist Memory::getFat_id(){
	return fat_id[fileIndex];
}

void Memory::setSector_ent(fatent sec_ent, int pos){
	sector_ent[pos]=sec_ent;
}

fatent Memory::getSector_ent(int pos){
	return sector_ent[pos];
}