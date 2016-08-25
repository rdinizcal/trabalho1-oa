#include <iostream>
#include <fstream>
#include <string>

void writeMemory(Memory memory){

	std::ifstream file;

	std::string fileName;
	std::string filePath;
	std::string txt = ".txt";

	int bytes,sectors,clusters;

	unsigned char buffer[512];

	clear();

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

			if(bytes<512)
				file.get(buffer[bytes++]);
			else{
				bytes=0;
				sector++;
			}

			if(sectors==4)
				memory.insertMemory(&buffer, clusters++);

			



		}
		

	}

	file.close();
}