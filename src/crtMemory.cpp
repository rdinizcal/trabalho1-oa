#include "../lib/crtMemory.h"
#include "../lib/utils.h"

#include <iostream>
#include <fstream>
#include <string>


/**************************CONSTRUTOR**************************/
CrtMemory::CrtMemory(){
	std::cout<<"Objeto de crtMemory criado."<<std::endl;
}

/**************************METODOS PUBLICOS**************************/
void CrtMemory::writeMemory(Memory memory){

	Utils util;

	std::ifstream file;

	std::string fileName;
	std::string filePath;
	std::string txt = ".txt";

	int bytes,sectors,clusters;

	unsigned char buffer[2048];

	util.clear();

	std::cout<<"Nome do arquivo: ";
	std::cin>>fileName;

	filePath.append("../").append(fileName).append(txt);

	file.open(filePath.c_str());

	if(!file.is_open()){

		//Nao funcional...
		std::cout<<"\nO arquivo "<<fileName<<" nao pode ser aberto."<<std::endl;
		std::cout<<"Pressione ENTER para continuar...\n";
		std::cin.clear();
		std::cin.ignore();

	}else{

		bytes=0;
		sectors=0;
		clusters=0;
		while(!file.eof()){

			file.read((char*)&buffer[bytes++], sizeof(unsigned char));

			if(bytes%512==0) 
				sectors++;

			if(sectors==4) 
				memory.insertMemory(buffer, clusters++);

		}
		

	}

	file.close();
}

void CrtMemory::readMemory(Memory memory){};
void CrtMemory::eraseMemory(Memory memory){};