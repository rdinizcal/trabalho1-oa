#include <iostream>

#include "../lib/utils.h"
#include "../lib/memory.h"
#include "../lib/crtMemory.h"

int main (){

	int choice=0;
	Memory myMemory;

	while(true){

		clear();

		std::cout<<"**********MENU PRINCIPAL**********"<<std::endl;
		std::cout<<"* 1 - Escrever Arquivo           *"<<std::endl;
		std::cout<<"* 2 - Ler Arquivo                *"<<std::endl;
		std::cout<<"* 3 - Apagar Arquivo             *"<<std::endl;
		std::cout<<"* 4 - Mostrar Tabela FAT         *"<<std::endl;
		std::cout<<"* 5 - Sair                       *"<<std::endl;
		std::cout<<"**********************************\n"<<std::endl;

		std::cout<<"Escolha um item: ";
		std::cin>>choice;

		if(choice>5 || choice<=0) return 0;
			
		switch(choice){
			case 1:
				writeMemory(myMemory);
				break;
			case 2:
				readMemory(myMemory);
				break;
			case 3:
				eraseMemory(myMemory);
				break;
			case 4:
				memory.showFAT();
				break;
			case 5:
				return 0;
		}

		std::cin.ignore();
	}

	return 0;
}