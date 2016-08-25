#include "../lib/memory.h"

#include <iostream>

#define MAXCYLINDER 10
#define MAXSECTOR 3000


/*Construtor*/
Memory::Memory(){
	cylinder = new track_array[MAXCYLINDER];
	fat_id = new fatlist;
	sector_ent = new fatent[MAXSECTOR];

	std::cout<<"Objeto de memoria criado."<<std::endl;
}

/*Destructor*/
Memory::~Memory(){
	delete[] cylinder;
	delete[] fat_id;
	delete[] sector_ent;

	std::cout<<"Objeto de memoria destruido."<<std::endl;
}


/**************************METODOS PUBLICOS**************************/
void Memory::insertMemory(unsigned char *buffer, int cluster){

	int pos = Memory::findEmptyCluster(0,0);

	if(pos==-1){
		std::cout<<"ERRO: Não foi possivel inserir o registro na memoria - ";
		std::cout<<"O disco esta cheio."<<std::endl;
		return;
	}

	std::cout<<pos<<std::endl;


}

void Memory::selectMemory(){

}

void Memory::deleteMemory(){

}

void Memory::showFAT(){

}

/**************************SETTERS & GETTERS**************************/
track_array* Memory::getCylinder(){
	return cylinder;
}

/**************************METODOS PRIVADOS**************************/
int Memory::findEmptyCluster(int pos, int emptyCounter){

	if(pos>MAXSECTOR) return-1;
	if(emptyCounter==3) return pos-3;

	return (sector_ent[pos].used==0?Memory::findEmptyCluster(pos+1,emptyCounter+1):Memory::findEmptyCluster(pos+1,0));
}

