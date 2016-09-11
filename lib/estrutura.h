#ifndef ESTRUTURA_H
#define ESTRUTURA_H

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

/*Estrutura que representa o array indicador de nome 
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

typedef struct sector_map {
	int fat_pos;
	int sector;
	int track;
	int cylinder;
	bool found;
}sector_map;

#endif