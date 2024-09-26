#include <stdint.h>
#include <random>
#include "chip8.hpp"
#include <iostream>
#include <fstream>


	void CPU::OP_00E0(){
			//clears screen (here we set video buffer to 0)
			memset(video_buffer,0,sizeof(video_buffer));
		}
		void CPU::OneNNN(){
			//gets the pc to jump to an address
			uint16_t address = opcode & 0x0FFFu; 
			pc = address;
		}
		void CPU::SIXXNN(){
			//sets register vx to a value
			uint8_t value = opcode & 0x00FF;
			uint8_t vx = (opcode & 0x0F00) >> 8;
			registers[vx] = value;
		}
		void CPU::SevenXNN(){
			//adds a value to register vx			
			uint8_t value = opcode & 0x00FF;
			uint8_t vx = (opcode & 0x0F00) >> 8;
			registers[vx] += value;
		};
		void CPU::ANNN(){
			uint16_t byte3 = opcode & 0x0FFF;
			index_register = byte3;
		};
		void CPU::DXYN(){
			uint8_t vx = (opcode & 0x0F00) >> 8;
			uint8_t vy = (opcode & 0x00F0) >> 4;
			uint8_t height = (opcode & 0x000F);

			uint8_t x_pos = registers[vx] % MAX_WIDTH;
			uint8_t y_pos = registers[vy] % MAX_HEIGHT;

      std::cout << "The X and y pos are " << +registers[vx] << ',' << +registers[vy] << '\n';

			registers[15] = 0;

			for(int row=0; row<height; row++){
				uint8_t spriteByte = memory[index_register + row];
				for(int col = 0; col < 8; col++)
				{
          if (x_pos+col > MAX_WIDTH) {break;}
					uint8_t spritepixel = spriteByte & (0x80 >> col); //0x80 = 10000000 shift over by whatever collumn we're on to get current bit needed for screenpixel
					uint32_t * screenpixel = &video_buffer[(y_pos + row) * MAX_WIDTH + (x_pos + col)];
					// Sprite pixel is on
				if (spritepixel)
				{
				// Screen pixel also on - collision
				if (*screenpixel == 0xFFFFFFFF)
				{
					registers[0xF] = 1;
				}

				// Effectively XOR with the sprite pixel
				*screenpixel ^= 0xFFFFFFFF;
			}
		}
	


				}

			}
		
const unsigned int START_ADDRESS = 0x200;
const unsigned int FONTSET_START_ADDRESS = 0x50;

CPU::CPU() {

  pc = START_ADDRESS;

  for (unsigned int i = 0; i < 80; ++i) {

    memory[FONTSET_START_ADDRESS + i] = fontset[i];
  }
}

void CPU::LoadROM(char const *filename) {

  std::ifstream file(filename, std::ios::binary | std::ios::ate);

  if (file.is_open()) {

    // get size of a file and create a buffer to hold the contents
    std::streampos size = file.tellg();
    char *buffer = new char[size];

    // go to the beggining of the file and fill the buffer
    file.seekg(0, std::ios::beg);
    file.read(buffer, size);
    file.close();

    // load the ROM contents into the Chip8's memory, starting at the 0x200
    for (long i = 0; i < size; ++i) {

      memory[START_ADDRESS + i] = buffer[i];
    }

    std::cout << memory[514];
    // Free the buffer
    delete[] buffer;
  }
}

void CPU::Cycle() {
  opcode = (memory[pc] << 8) | memory[pc + 1];
  pc += 2;
  std::cout << pc << " ";
  switch (opcode & 0xF000) {
  case 0x0000:
    OP_00E0();
    std::cout << "00E0" << '\n';
    break;
  case 0x1000:
    OneNNN();
    std::cout << "1NNN" << '\n';
    break;
  case 0x6000:
    SIXXNN();
    std::cout << "6XNN" << '\n';
    break;
  case 0x7000:
    SevenXNN();
    std::cout << "7XNN" << '\n';
    break;
  case 0xA000:
    ANNN();
    std::cout << "ANNN" << '\n';
    break;
  case 0xD000:
    DXYN();
    std::cout << "DXYN" << '\n';
  }
}
