#include <iostream>
#include <string>
#include <fstream>

#include "estrutura.hpp"

void clear();
void escreverNaMem();
void lerDaMem();
void apagarDaMem();
void imprimirFAT();

int main (){

	int choice=0;

	while(true){

		clear();
		
		std::cout<<"**********MENU PRINCIPAL**********"<<std::endl;
		std::cout<<"* 1 - Escrever arquivo           *"<<std::endl;
		std::cout<<"* 2 - Ler Arquivo                *"<<std::endl;
		std::cout<<"* 3 - Apagar Arquivo             *"<<std::endl;
		std::cout<<"* 4 - Mostrar Tabela FAT         *"<<std::endl;
		std::cout<<"* 5 - Sair                       *"<<std::endl;
		std::cout<<"**********************************\n"<<std::endl;

		std::cout<<"Escolha um item: ";
		std::cin>>choice;

		if(choice>=5 || choice<=0) break;
			
		switch(choice){
			case 1:
				escreverNaMem();
				break;
			case 2:
				lerDaMem();
				break;
			case 3:
				apagarDaMem();
				break;
			case 4:
				imprimirFAT();
				break;
		}
		break;
	}

	return 0;
}

void clear(){
	std::cout << "\033[2J\033[1;1H";
}

void escreverNaMem(){

	std::ifstream file;

	std::string fileName;
	std::string txt = ".txt";

	int pos;
	char* buffer = new char;

	clear();

	std::cout<<"Nome do arquivo: ";
	std::cin>>fileName;

	file.open(fileName.append(txt).c_str());

	if(!file.is_open()){

		//Nao funcional...
		std::cout<<"\nO arquivo "<<fileName<<" nao pode ser aberto."<<std::endl;
		std::cout<<"Pressione ENTER para continuar...\n";
		std::cin.clear();
		std::cin.ignore();

	}else{

		pos=0;
		for(unsigned char byte; file.read((&byte), sizeof(byte));pos++)
			buffer[pos] = byte;
		
		
		

	}

	delete[] buffer;
	file.close();
}

void lerDaMem(){}

void apagarDaMem(){}

void imprimirFAT(){}