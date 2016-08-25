#include "../lib/utils.h"

#include <iostream>
//#include <fstream>

void clear(){
	std::cout << "\033[2J\033[1;1H";
}

/*std::ifstream::pos_type filesize(const char* fileName){
    std::ifstream file(fileName, std::ifstream::ate | std::ifstream::binary);
    return file.tellg(); 
}*/