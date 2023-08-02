#include "chip8.hpp"
#include <fstream>
#include <chrono>
#include <random>

const unsigned int START_ADDRESS = 0x200;
const unsigned int FONTSET_START_ADDRESS = 0x50;

CPU::CPU(){

	pc = START_ADDRESS;

		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		:randGen(seed)
	for(unsigned int i =0; i < 80; ++i){

		memory[FONTSET_START_ADDRESS + i] = fontset[i]; 

	}

}


void CPU::LoadROM(char const* filename){

	std::ifstream file(filename, std::ios::binary | std::ios::ate);

	if(file.is_open()){

		//get size of a file and create a buffer to hold the contents
		std::streampos size = file.tellg();
		char* buffer = new char[size];

		//go to the beggining of the file and fill the buffer
		file.seekg(0, std::ios::beg);
		file.read(buffer, size);
		file.close();

		//load the ROM contents into the Chip8's memory, starting at the 0x200
		for(long i = 0; i<size; ++i){

			memory[START_ADDRESS + i] = buffer[i];		

		}
		//Free the buffer
		delete[] buffer;

	}
}
