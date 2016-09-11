#include "../lib/crtMemory.h"
#include "../lib/utils.h"

#include <iostream>
#include <fstream>
#include <string>


/**************************CONSTRUTOR**************************/
CrtMemory::CrtMemory(){
	//std::cout<<"Objeto de crtMemory criado."<<std::endl;
}

/**************************METODOS PUBLICOS**************************/
void CrtMemory::writeMemory(Memory* memory){

	Utils util;

	std::ifstream file;

	std::string fileName;
	std::string filePath;
	std::string txt = ".txt";

	bool inserted = false;

	int bytes,sectors,clusters;
	int insertedSectors[3000];

	unsigned char buffer[2048];

	fatlist fileId;
	sector_map map;
	fatent sec_ent;

	util.clear();

	std::cout<<"Nome do arquivo: ";
	std::cin>>fileName;
	//fileName="medium";
	fileName.append(txt);
	filePath.append("../").append(fileName);

	file.open(filePath.c_str());

	std::cout<<filePath<<std::endl;

	if(file.is_open()){
		//std::cout<<"ABRE O ARQUIVO";
		bytes=0;
		sectors=0;
		clusters=0;
		while(!file.eof()){

			file.read((char*)&buffer[bytes], sizeof(unsigned char));

			//std::cout<<buffer[bytes];
			
			bytes++;
			if(bytes%512==0){ 
				sectors++;
				std::cout<<"Sectors Read: "<<sectors<<std::endl;
			}
			if(sectors==4){ 
				sectors=0;

				std::cout<<"*memory= "<<memory<<std::endl;

				if(clusters==0){
					map=findEmptyCluster(memory);

					if(!map.found){
						std::cout<<"ERRO: Não foi possivel inserir o registro na memoria - ";
						std::cout<<"O disco esta cheio."<<std::endl;
						return;
					}

					std::copy(fileName.begin(),fileName.end(),fileId.file_name);
					fileId.first_sector=map.fat_pos;

					memory->setFat_id(fileId);

				}else{
					map=findNextEmptyCluster(memory,map);
					if(!map.found){
						std::cout<<"ERRO: Não foi possivel inserir o registro na memoria - ";
						std::cout<<"O disco esta cheio."<<std::endl;
						return;
					}
				}

				sec_ent.used=1;
				for(int i=0; i<4; i++){ 
					memory->setSector_ent(sec_ent,map.fat_pos+i);
					insertedSectors[i+(clusters*4)]=map.fat_pos+i;
				}
				memory->insertMemory(buffer, map);
				std::cout<<"Cluster "<<clusters+1<<" inserido!"<<std::endl;
				clusters++;
				inserted=true;
			}

		}
		std::cout<<"Sectors to insert: "<<sectors<<std::endl; 
		if(sectors!=0){

			for(int i=sectors; i<4; i++){
				for(int j=0; j<512; j++){
					buffer[j+(512*i)]=0x0;
				}
			}

			if(!inserted){
				map=findEmptyCluster(memory);

				if(!map.found){
					std::cout<<"ERRO: Não foi possivel inserir o registro na memoria - ";
					std::cout<<"O disco esta cheio."<<std::endl;
					return;
				}

				std::copy(fileName.begin(),fileName.end(),fileId.file_name);
				fileId.first_sector=map.fat_pos;

				memory->setFat_id(fileId);
			}else{
				map=findNextEmptyCluster(memory,map);
				if(!map.found){
					std::cout<<"ERRO: Não foi possivel inserir o registro na memoria - ";
					std::cout<<"O disco esta cheio."<<std::endl;
					return;
				}
			}
			sec_ent.used=1;
			for(int i=0; i<4; i++){ 
				memory->setSector_ent(sec_ent,map.fat_pos+i);
				insertedSectors[i+(clusters*4)]=map.fat_pos+i;
			}
			memory->insertMemory(buffer, map);
			std::cout<<"Cluster "<<clusters+1<<" inserido!"<<std::endl;
			clusters++;
			inserted=true;
		}

		/*std::cout<<"insertedSectors: ";
		for(int i=0; i<clusters*4; i++)	std::cout<<insertedSectors[i]<<" ";
		std::cout<<std::endl;*/

		std::cout<<"Completando os next e eof..."<<std::endl;
		for(int i=0; i<clusters*4; i++){
			std::cout<<insertedSectors[i]<<" ";

			if(i+1<clusters*4){
				sec_ent.next=insertedSectors[i+1];
				memory->setSector_ent(sec_ent,insertedSectors[i]);
			}else{
				sec_ent.eof=1;
				sec_ent.next=0;
				memory->setSector_ent(sec_ent,insertedSectors[i]);
			}
		}

	}else{
		std::cout<<"Arquivo nao pode ser aberto";

	}
	std::cout<<std::endl<<"Closing file..."<<std::endl;
	file.close();
	std::cout<<"File Closed!"<<std::endl;

	memory->printAttribute();

}

void CrtMemory::readMemory(Memory* memory){};
void CrtMemory::eraseMemory(Memory* memory){};


/**************************METODOS PRIVADOS**************************/
sector_map CrtMemory::findEmptyCluster(Memory* memory){

	std::cout<<"Procurando cluster vazio na memoria..."<<std::endl;
	sector_map map;
	int emptySectorCounter=0;
	int pos=0;

	for(int tracks=0; tracks<5; tracks++){
		//std::cout<<"Track: "<<tracks<<std::endl;
		for(int cylinders=0; cylinders<10; cylinders++){
			//std::cout<<"Cylinder: "<<cylinders<<std::endl;
			emptySectorCounter=0;
			for(int sectors=0; sectors<60; sectors++){
				pos = cylinders*300+tracks*60+sectors;
				//std::cout<<pos<<", ";
				emptySectorCounter = memory->getSector_ent(pos).used==0?emptySectorCounter+1:0;
				if(emptySectorCounter==4) {
					map.fat_pos=pos-3;
					map.sector=sectors-3;
					map.track=tracks;
					map.cylinder=cylinders;
					map.found=true;
					std::cout<<"Encontrei!"<<std::endl;
					return map;
				}
			}
		}
	}

	map.found=false;
	return map;
}

sector_map CrtMemory::findNextEmptyCluster(Memory* memory, sector_map lastMap){

	std::cout<<"Procurando proximo cluster vazio na memoria..."<<std::endl;
	sector_map map;
	int emptySectorCounter=0;
	int pos=0;

	int cylinders = lastMap.cylinder;
	int sectors = lastMap.sector;

	//std::cout<<"Cylinder: "<<lastMap.cylinder<<" Track: "<<lastMap.track+1<<" Sector: "<<lastMap.sector<<std::endl;

	//memory->printAttribute();

	for(int tracks=lastMap.track+1; tracks<5; tracks++){

		pos = cylinders*300+tracks*60+sectors;
		//std::cout<<"pos: "<<pos<<std::endl;

		for(int i=0; i<4; i++)
			emptySectorCounter = memory->getSector_ent(pos+i).used==0?emptySectorCounter+1:0;
		
		if(emptySectorCounter==4){ 
			map.fat_pos=pos;
			map.sector=sectors;
			map.track=tracks;
			map.cylinder=cylinders;
			map.found=true;
			std::cout<<"Encontrei!"<<std::endl;
			return map;
		}
	}	

	return findEmptyCluster(memory);
}

void CrtMemory::voidMethodTest(Memory* memory){
	memory->printAttribute();
}