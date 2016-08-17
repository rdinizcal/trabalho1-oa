#include <iostream>
#include <string>

/*Estutura que representa 1 setor que contem 512 bytes*/
typedef struct block {
	unsigned char bytes_s[512];
}block;

/*Estrutura que representa 1 trilha que contem 60 setores*/
typedef struct sector_array {
	block sector[60];
}sector_array;

/*Estrutura que representa 1 cilindro que contem 5 trilhas*/
typedef struct track_array {
	sector_array track[5];
}track_array;

/*Estrutura que representa o primeiro array indicador de nome 
do arquivo e indicador do primeiro setor da tabela FAT*/
typedef struct fatlist_s {
	char file_name[100];
	unsigned int first_sector;
}fatlist;

/*Estrutura que representa uma lista com uma entrada para 
cada setor do disco rigido*/
typedef struct fatent_s {
	unsigned int used;
	unsigned int eof;
	unsigned int next;
}fatent;

void escreverNaMem();
void lerDaMem();
void apagarDaMem();
void imprimirFAT();

int main (){

	int choice=0;

	while(true){
		std::cout<<"**********MENU PRINCIPAL**********"<<std::endl;
		std::cout<<"1 - Escrever Arquivo"<<std::endl;
		std::cout<<"2 - Ler Arquivo"<<std::endl;
		std::cout<<"3 - Apagar Arquivo"<<std::endl;
		std::cout<<"4 - Mostrar Tabela FAT"<<std::endl;
		std::cout<<"5 - Sair"<<std::endl;
		std::cout<<"**********************************\n"<<std::endl;

		std::cout<<"Escolha um item para continuar: ";
		std::cin>>choice;

		if(choice==5) break;
		if(choice>5 || choice<=0) continue;
			
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

	}
	return 0;
}

void escreverNaMem(){

	std::string fileName;

	std::cout<<"Nome do arquivo: ";
	std::cin>>fileName;
}

void lerDaMem(){}

void apagarDaMem(){}

void imprimirFAT(){}