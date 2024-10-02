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
      //sets index register to value NNN (last 3 nibbles)
			uint16_t byte3 = opcode & 0x0FFF;
			index_register = byte3;
		};
    
    void CPU::OP_BNNN(){
      //jumps to address NNN + value in V0
      //TODO: Add configuration to switch between this function definition and one that instead adds VX to address NNN (started with CHIP-48 and SUPER-CHIP)
      pc = (opcode & 0x0FFF) + registers[0];
    }
		void CPU::DXYN(){
      //Draw Function
			uint8_t vx = (opcode & 0x0F00) >> 8;
			uint8_t vy = (opcode & 0x00F0) >> 4;
			uint8_t height = (opcode & 0x000F);

			uint8_t x_pos = registers[vx] % MAX_WIDTH;
			uint8_t y_pos = registers[vy] % MAX_HEIGHT;

      std::cout << "The X and y pos are " << +registers[vx] << ',' << +registers[vy] << '\n';

			registers[15] = 0;
      /*
       loop through sprite located at memory held in the index register
       XOR sprite bit with screen bit
       if inital x or y value is not within screen bounds than wrap sprite
       but if during the drawing we exceed the screen bounds than simply clip the sprite
       */
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
  void CPU::OP_2NNN(){
    //Add current address to the stack and jump to memory location NNN
    stack[sp] = pc;
    ++sp;
    pc = (opcode & 0x0FFF);
  }

  void CPU::OP_00EE(){
    //Return back to courotine (like a break)
    --sp;
    pc = stack[sp];
    stack[sp] = 0x00;
  }

  void CPU::OP_3XNN(){
    //if the value in VX == NN than skip to the next instruction (increment program counter by 2)
    uint8_t VX = registers[(opcode & 0x0F00) >> 8];
    if (VX == (opcode & 0x00FF)){
       pc += 2;
    }
  }
  void CPU::OP_4XNN(){
    //if the value in VX != NN than skip to the next instruction (increment program counter by 2)
    uint8_t VX = registers[(opcode & 0x0F00) >> 8];
    if (VX != (opcode & 0x00FF)){
       pc += 2;
    }
  }
  void CPU::OP_5XY0(){
    //if the value in VX == VY than skip to the next instruction (increment program counter by 2)
    uint8_t VX = registers[(opcode & 0x0F00) >> 8];
    uint8_t VY = registers[(opcode & 0x00F0) >> 4];
    if (VX == VY){
       pc += 2;
    }
  }
  void CPU::OP_9XY0(){
    //if the value in VX != VY than skip to the next instruction (increment program counter by 2)
    uint8_t VX = registers[(opcode & 0x0F00) >> 8];
    uint8_t VY = registers[(opcode & 0x00F0) >> 4];
    if (VX != VY){
       pc += 2;
    }
  }
  void CPU::OP_8XY0(){
    //Set VX = to VY
    uint8_t *VX = &registers[(opcode & 0x0F00) >> 8];
    uint8_t VY = registers[(opcode & 0x00F0) >> 4];
    *VX = VY;
  }

  void CPU::OP_8XY1(){
    //VX = BITWISE OR VX and VY
    uint8_t *VX = &registers[(opcode & 0x0F00) >> 8];
    uint8_t VY = registers[(opcode & 0x00F0) >> 4];
    *VX = *VX | VY;
  }

  void CPU::OP_8XY2(){
    //VX = BITWISE AND VX and VY
    uint8_t *VX = &registers[(opcode & 0x0F00) >> 8];
    uint8_t VY = registers[(opcode & 0x00F0) >> 4];
    *VX = *VX & VY;
  }
		
  void CPU::OP_8XY3(){
    //VX = BITWISE XOR VX and VY
    uint8_t *VX = &registers[(opcode & 0x0F00) >> 8];
    uint8_t VY = registers[(opcode & 0x00F0) >> 4];
    *VX = *VX^VY;
  }

  void CPU::OP_8XY4(){
    //Add VX+VY if the result is greater than 8bits (255) than set the carry flag to 1 (VF=1) and set VX only equal to the last 8 bits of the addition
    uint8_t *VX = &registers[(opcode & 0x0F00) >> 8];
    uint8_t VY = registers[(opcode & 0x00F0) >> 4];
    if (*VX+VY > 255) {
      registers[15] = 1;
    }
    else {
      registers[15] = 0;  
    }
    *VX = (*VX+VY) & 0xFF;
  }

  void CPU::OP_8XY5(){
    //VX =  VX-VY
    uint8_t *VX = &registers[(opcode & 0x0F00) >> 8];
    uint8_t VY = registers[(opcode & 0x00F0) >> 4];
    *VX = *VX-VY;
  }

  void CPU::OP_8XY7(){
    //VX = VY-VX
    uint8_t *VX = &registers[(opcode & 0x0F00) >> 8];
    uint8_t VY = registers[(opcode & 0x00F0) >> 4];
    *VX = VY-*VX;
  }

  void CPU::OP_8XY6(){
    //Set VX to VY and shift VX to the right by 1 bit
    //Set the VF flag to the bit that was shifted out
    uint8_t *VX = &registers[(opcode & 0x0F00) >> 8];
    uint8_t VY = registers[(opcode & 0x00F0) >> 4];
    *VX=VY;
    registers[15] = *VX & 0b10000000; 
    *VX >> 1;
  }

  void CPU::OP_8XYE(){
    //Set VX to VY and shift VX to the left by 1 bit
    uint8_t *VX = &registers[(opcode & 0x0F00) >> 8];
    uint8_t VY = registers[(opcode & 0x00F0) >> 4];
    *VX=VY;
    registers[15] = *VX & 0b10000000; 
    *VX << 1;
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
