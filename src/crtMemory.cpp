#include "../lib/crtMemory.h"
#include "../lib/utils.h"
#include "../lib/estrutura.h"

/**************************CONSTRUTOR**************************/
CrtMemory::CrtMemory(){
	//std::cout<<"Objeto de crtMemory criado."<<std::endl;
}

/**************************METODOS PUBLICOS**************************/
bool CrtMemory::writeMemory(int files, Memory* memory){

	avg_seek=0;
	min_seek=0;
	lat=0;
	transfer=0;

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
	fileName.append(txt);

	
	if(fileExists(files, fileName, memory)){
		std::cout<<"ERRO: Ja existe um arquivo com esse nome no HD"<<std::endl;
		return false;
	}

	filePath.append("../").append(fileName);

	file.open(filePath.c_str());

	//std::cout<<filePath<<std::endl;

	if(file.is_open()){
		bytes=0;
		sectors=0;
		clusters=0;
		while(!file.eof()){

			file.read((char*)&buffer[bytes], sizeof(unsigned char));
			
			bytes++;
			if(bytes%512==0){ 
				sectors++;
				//std::cout<<"Sectors Read: "<<sectors<<std::endl;
			}
			if(sectors==4){ 
				sectors=0;

				//std::cout<<"*memory= "<<memory<<std::endl;

				if(clusters==0){
					map=findEmptyCluster(memory);

					if(!map.found){
						std::cout<<"ERRO: Não foi possivel inserir o registro na memoria - ";
						std::cout<<"O disco esta cheio."<<std::endl;
						file.close();
						return false;
					}

					fileName.copy(fileId.file_name,fileName.size(),0);
					fileId.file_name[fileName.size()]='\0';
					fileId.first_sector=map.fat_pos;

					memory->setFat_id(fileId);

				}else{
					map=findNextEmptyCluster(memory,map);
					if(!map.found){
						std::cout<<"ERRO: Não foi possivel inserir o registro na memoria - ";
						std::cout<<"O disco esta cheio."<<std::endl;
						file.close();
						return false;
					}
				}

				sec_ent.used=1;
				for(int i=0; i<4; i++){ 
					memory->setSector_ent(sec_ent,map.fat_pos+i);
					insertedSectors[i+(clusters*4)]=map.fat_pos+i;
				}
				memory->insertMemory(buffer, map);
				transfer+=4;
				//std::cout<<"Cluster "<<clusters+1<<" inserido!"<<std::endl;
				clusters++;
				inserted=true;
				bytes=0;
			}

		}
		std::cout<<"Bytes to insert: "<<2048-bytes<<std::endl; 
		if(sectors!=0 || bytes>0){

			for(int i=bytes-1; i<2048; i++)
				buffer[i]=0x0;

			/*for(int i=sectors; i<4; i++){
				for(int j=0; j<512; j++){
					buffer[j+(512*i)]=0x0;
				}
			}*/

			if(!inserted){
				map=findEmptyCluster(memory);

				if(!map.found){
					std::cout<<"ERRO: Não foi possivel inserir o registro na memoria - ";
					std::cout<<"O disco esta cheio."<<std::endl;
					file.close();
					return false;
				}

				std::copy(fileName.begin(),fileName.end(),fileId.file_name);
				fileId.first_sector=map.fat_pos;

				memory->setFat_id(fileId);
			}else{
				map=findNextEmptyCluster(memory,map);
				if(!map.found){
					std::cout<<"ERRO: Não foi possivel inserir o registro na memoria - ";
					std::cout<<"O disco esta cheio."<<std::endl;
					file.close();
					return false;
				}
			}
			sec_ent.used=1;
			for(int i=0; i<4; i++){ 
				memory->setSector_ent(sec_ent,map.fat_pos+i);
				insertedSectors[i+(clusters*4)]=map.fat_pos+i;
			}
			memory->insertMemory(buffer, map);
			transfer+=4;
			//std::cout<<"Cluster "<<clusters+1<<" inserido!"<<std::endl;
			clusters++;
			inserted=true;
		}

		//std::cout<<"Completando os next e eof..."<<std::endl;
		for(int i=0; i<clusters*4; i++){
			//std::cout<<insertedSectors[i]<<" ";

			if(i+1<clusters*4){
				sec_ent.eof=0;
				sec_ent.next=insertedSectors[i+1];
			}else{
				sec_ent.eof=1;
				sec_ent.next=0;
			}
			memory->setSector_ent(sec_ent,insertedSectors[i]);

		}

	}else{
		std::cout<<"Arquivo nao pode ser aberto";
		file.close();
		return false;

	}
	file.close();

	std::cout<<"O arquivo "<<fileName<<" foi inserido com sucesso!"<<std::endl;
	std::cout<<"A operacao de insercao durou "<<4*avg_seek+1*min_seek+6*lat+0.2*transfer<<"ms."<<std::endl;
	
	return true;
}

bool CrtMemory::readMemory(int files, Memory* memory){

	avg_seek=0;
	min_seek=0;
	lat=0;
	transfer=0;

	std::ofstream file;

	std::string fileName;
	std::string filePath;
	std::string txt = ".txt";

	int pos=0;
	int sectors[3000];

	unsigned char buffer[2048];

	fatent ent;
	sector_map map;

	Utils util;

	util.clear();
	
	std::cout<<"Nome do arquivo: ";
	std::cin>>fileName;
	fileName.append(txt);

	if(!fileExists(files, fileName, memory)){
		std::cout<<"ERRO: O arquivo nao foi encontrado no HD"<<std::endl;
		return false;
	}

	filePath.append("../").append("saida.txt");

	file.open(filePath.c_str());

	if(file.is_open()){
		int i=0;
		pos=(int)findFirstSector(files, fileName, memory);

		while(true){
			sectors[i++]=pos;
			ent=memory->getSector_ent(pos+3);
			pos=ent.next;
			if(ent.eof==1) break;
		}

		for(int j=0; j<i; j++){
			avg_seek++;
			lat++;
			map=posToMap(sectors[j]);
			transfer++;
			memory->selectMemory(buffer, map);

			for(int k=0; k<2048; k++)
				if(buffer[k]!='\00') file<<buffer[k];
			
		}

	}else{
		std::cout<<"Arquivo nao pode ser aberto";
		file.close();
		return false;
	}

	file.close();

	std::cout<<"O arquivo "<<fileName<<" foi lido com sucesso!"<<std::endl;
	std::cout<<"A operacao de leitura durou "<<4*avg_seek+1*min_seek+6*lat+0.2*transfer<<"ms."<<std::endl;
	
	return true;
}

bool CrtMemory::eraseMemory(int files, Memory* memory){

	std::string fileName;
	std::string txt = ".txt";

	int pos=0;

	//fatent ent;

	Utils util;
	util.clear();
	
	std::cout<<"Nome do arquivo: ";
	std::cin>>fileName;
	fileName.append(txt);


	if(!fileExists(files, fileName, memory)){
		std::cout<<"ERRO: O arquivo nao foi encontrado no HD"<<std::endl;
		return false;
	}

	pos=(int)findFirstSector(files, fileName, memory);

	memory->deleteMemory(fileName, pos);
	
	std::cout<<"O arquivo "<<fileName<<" foi removido com sucesso!"<<std::endl;
	
	return true;
}

void CrtMemory::showFAT(int files, Memory* memory){

	Utils util;

	fatlist nameList;
	fatent ent;

	std::string fileName;
	int fileSize=0;
	int sectors[3000];

	int pos;

	util.clear();

	std::cout<<"NOME:\t\tTAMANHO EM DISCO:\t\tLOCALIZAÇÃO:"<<std::endl;

	for(int i=0; i<files; i++){
		nameList=memory->getFat_id(i);

		fileName=nameList.file_name;
		pos=nameList.first_sector;

		fileSize=0;
		while(true){
			ent=memory->getSector_ent(pos);
			sectors[fileSize]=pos;
			pos=ent.next;
			fileSize++;
			if(ent.eof==1) break;
		}

		std::cout<<fileName<<"\t"<<fileSize*512<<" Bytes\t\t\t";

		for(int j=0; j<fileSize; j++){
			std::cout<<sectors[j];
			if(j+1<fileSize) std::cout<<", ";
			else std::cout<<std::endl;
		}
	}
}


/**************************METODOS PRIVADOS**************************/
int CrtMemory::mapToPos(sector_map map){
	
	int pos = map.cylinder*300+map.track*60+map.sector;

	return pos;
}

sector_map CrtMemory::posToMap(int pos){

	sector_map map;

	map.cylinder=pos/300;
	map.track=(pos-(map.cylinder*300))/60;
	map.sector=(pos-(map.cylinder*300+map.track*60));

	return map;
}

unsigned int CrtMemory::findFirstSector(int files, std::string name, Memory* memory){

	std::string actualFilename;

	avg_seek++;

	for(int i=0; i<files; i++){
		actualFilename.clear();
		actualFilename = memory->getFat_id(i).file_name;
		if(actualFilename.compare(name)==0) return memory->getFat_id(i).first_sector;
	}

	return 0x0;
}

bool CrtMemory::fileExists(int files, std::string name, Memory* memory){

	std::string actualFilename;

	for(int i=0; i<files; i++){
		actualFilename.clear();
		actualFilename = memory->getFat_id(i).file_name;
		if(actualFilename.compare(name)==0) return true;
	}

	return false;
}

sector_map CrtMemory::findEmptyCluster(Memory* memory){

	//std::cout<<"Procurando cluster vazio na memoria..."<<std::endl;
	sector_map map;
	int emptySectorCounter=0;
	int pos=0;

	for(int tracks=0; tracks<5; tracks++){
		//std::cout<<"Track: "<<tracks<<std::endl;
		avg_seek++;
		for(int cylinders=0; cylinders<10; cylinders++){
			min_seek++;
			//std::cout<<"Cylinder: "<<cylinders<<std::endl;
			emptySectorCounter=0;
			for(int sectors=0; sectors<60; sectors++){
				lat++;
				pos = cylinders*300+tracks*60+sectors;
				//std::cout<<pos<<", ";
				emptySectorCounter = memory->getSector_ent(pos).used==0?emptySectorCounter+1:0;
				if(emptySectorCounter==4) {
					map.fat_pos=pos-3;
					map.sector=sectors-3;
					map.track=tracks;
					map.cylinder=cylinders;
					map.found=true;
					//std::cout<<"Encontrei!"<<std::endl;
					return map;
				}
			}
		}
	}

	map.found=false;
	return map;
}

sector_map CrtMemory::findNextEmptyCluster(Memory* memory, sector_map lastMap){

	//std::cout<<"Procurando proximo cluster vazio na memoria..."<<std::endl;
	sector_map map;
	int emptySectorCounter=0;
	int pos=0;

	int cylinders = lastMap.cylinder;
	int sectors = lastMap.sector;

	//std::cout<<"Cylinder: "<<lastMap.cylinder<<" Track: "<<lastMap.track+1<<" Sector: "<<lastMap.sector<<std::endl;

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
			//std::cout<<"Encontrei!"<<std::endl;
			return map;
		}
	}	

	return findEmptyCluster(memory);
}
