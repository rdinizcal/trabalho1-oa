#include "../lib/memory.h"

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

	//std::cout<<"Inserindo cluster na memoria..."<<std::endl;
	//std::cout<<"Cylinder: "<<map.cylinder<<" Track: "<<map.track<<" Sector: "<<map.sector<<std::endl;

	for(int i=0; i<4; i++){
		for(int j=0; j<512; j++){
			cylinder[map.cylinder].track[map.track].sector[map.sector+i].bytes_s[j] = buffer[j+(512*i)];
		}
	}

}

void Memory::selectMemory(unsigned char buffer[], sector_map map){

	//std::cout<<"Lendo cluster na memoria..."<<std::endl;
	//std::cout<<"Cylinder: "<<map.cylinder<<" Track: "<<map.track<<" Sector: "<<map.sector<<std::endl;

	for(int i=0; i<4; i++){
		for(int j=0; j<512; j++){
				buffer[j+(512*i)]=cylinder[map.cylinder].track[map.track].sector[map.sector+i].bytes_s[j];
		}
	}
}

void Memory::deleteMemory(std::string fileName, int pos){

	int prevPos;
	std::string actualFilename;
	int flag=0;

	while(true){
		prevPos=pos;
		pos=sector_ent[pos].next;

		sector_ent[prevPos].used=0;
		sector_ent[prevPos].next=0;
		if(sector_ent[prevPos].eof==1){
			sector_ent[prevPos].eof=0;
			break;
		}
	}

	for(int i=0; i<fileIndex+1; i++){

		if(flag==1){
			fat_id[i-1]=fat_id[i];
		}else{
			actualFilename.clear();
			actualFilename = fat_id[i].file_name;

			if(actualFilename.compare(fileName)==0)
				flag=1;
		}

	}

	fileIndex--;

}

/**************************SETTERS & GETTERS**************************/
void Memory::setFat_id(fatlist id){
	fat_id[fileIndex++]=id;
}

fatlist Memory::getFat_id(int pos){
	return fat_id[pos];
}

void Memory::setSector_ent(fatent sec_ent, int pos){
	sector_ent[pos]=sec_ent;
}

fatent Memory::getSector_ent(int pos){
	return sector_ent[pos];
}