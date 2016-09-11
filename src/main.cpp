#include <iostream>
#include <limits>

#include "../lib/utils.h"
#include "../lib/memory.h"
#include "../lib/crtMemory.h"

int main (){

	int choice=0;
	Memory *myMemory = new Memory;

	while(true){

		std::cout<<"Does it even get here?"<<std::endl;
		Utils util;
		CrtMemory memoryController;

		util.clear();

		std::cout<<"**********MENU PRINCIPAL**********"<<std::endl;
		std::cout<<"* 1 - Escrever Arquivo           *"<<std::endl;
		std::cout<<"* 2 - Ler Arquivo                *"<<std::endl;
		std::cout<<"* 3 - Apagar Arquivo             *"<<std::endl;
		std::cout<<"* 4 - Mostrar Tabela FAT         *"<<std::endl;
		std::cout<<"* 5 - Sair                       *"<<std::endl;
		std::cout<<"**********************************"<<std::endl;
		std::cout<<std::endl;

		std::cout<<"Escolha um item: ";
		std::cin>>choice;

		if(choice>5 || choice<=0) return 0;

		switch(choice){
			case 1:
				memoryController.writeMemory(myMemory);
				std::cout<<"Back to main"<<std::endl;
				break;
			case 2:
				memoryController.readMemory(myMemory);
				break;
			case 3:
				memoryController.eraseMemory(myMemory);
				break;
			case 4:
				myMemory->showFAT();
				break;
			case 5:
				return 0;
		}

	}

	delete[] myMemory;	/*
	std::cout << "Press enter to continue . . . ";
	std::cin.sync();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	*/
	return 0;
}