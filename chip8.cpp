#include "chip8.hpp"
#include <fstream>
#include <SDL2/SDL.h>
#include <iostream>

const unsigned int START_ADDRESS = 0x200;
const unsigned int FONTSET_START_ADDRESS = 0x50;

CPU::CPU(){

	pc = START_ADDRESS;
    
	for(unsigned int i =0; i < 80; ++i){

		memory[FONTSET_START_ADDRESS + i] = fontset[i]; 

	}

}


void CPU::LoadROM(char const* filename){

	std::ifstream file("ibm.ch8", std::ios::binary | std::ios::ate);

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

void CPU::Cycle(){
	opcode =  (memory[pc] << 8) | memory[pc+1];
	pc += 2;

	switch(opcode & 0xF000){
		case 0x0000:
			OP_00E0();
			break;
		case 0x1000:
			OneNNN();
			break;
		case 0x6000:
			SIXXNN();
			break;
		case 0x7000:
			SevenXNN();
			break;
		case 0xA000:
			ANNN();
			break;
		case 0xD000:
			//DXYN();
			break;
	}

	
}


int main(int argc, char* argv[]){

 SDL_Init( SDL_INIT_EVERYTHING );

    SDL_Window *window = SDL_CreateWindow( "Hello SDL World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 800, SDL_WINDOW_ALLOW_HIGHDPI );
    
    // Check that the window was successfully created
    if ( NULL == window )
    {
        // In the case that the window could not be made...
        std::cout << "Could not create window: " << SDL_GetError( ) << std::endl;
        return 1;
    }
    
    SDL_Event windowEvent;
    
    while ( true )
    {
        if ( SDL_PollEvent( &windowEvent ) )
        {
            if ( SDL_QUIT == windowEvent.type )
            {
                break;
            }
        }
    }
    
    SDL_DestroyWindow( window );
    SDL_Quit( );
    
    return EXIT_SUCCESS;
	}
	