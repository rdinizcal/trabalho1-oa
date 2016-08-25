#include "../lib/utils.h"

#include <iostream>
//#include <fstream>

/**************************CONSTRUTOR**************************/
Utils::Utils(){
	std::cout<<"Objeto de utils criado."<<std::endl;
}

/**************************METODOS PUBLICOS**************************/
void Utils::clear(){
	std::cout << "\033[2J\033[1;1H";
}

/*std::ifstream::pos_type filesize(const char* fileName){
    std::ifstream file(fileName, std::ifstream::ate | std::ifstream::binary);
    return file.tellg(); 
}*/