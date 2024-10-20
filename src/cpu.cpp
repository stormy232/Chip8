#include <stdint.h>
#include <chrono>
#include <random>
#include "chip8.hpp"
#include <iostream>
#include <fstream>
#include <time.h> 
#include <cstdlib>


	void CPU::OP_00E0(){
			//clears screen (here we set video buffer to 0)
			memset(video_buffer,0,sizeof(video_buffer));
		}
		void CPU::OneNNN(){
			//gets the pc to jump to an address
			uint16_t address = opcode & 0xFFFu; 
			pc = address;
		}
		void CPU::SIXXNN(){
			//sets register vx to a value
			uint8_t value = opcode & 0xFF;
			uint8_t vx = (opcode & 0x0F00) >> 8;
			registers[vx] = value;
		}
		void CPU::SevenXNN(){
			//adds a value to register vx			
			uint8_t value = opcode & 0xFF;
			uint8_t vx = (opcode & 0x0F00) >> 8;
			registers[vx] += value;
		};
		void CPU::ANNN(){
      //sets index register to value NNN (last 3 nibbles)
			uint16_t byte3 = opcode & 0xFFF;
			index_register = byte3;
		};
    
    void CPU::OP_BNNN(){
      //jumps to address NNN + value in V0
      //TODO: Add configuration to switch between this function definition and one that instead adds VX to address NNN (started with CHIP-48 and SUPER-CHIP)
      pc = (opcode & 0xFFF) + registers[0];
    }

    void CPU::OP_CXNN(){
			uint8_t *vx = &registers[(opcode & 0x0F00) >> 8];
      srand(time(0));
      int random = rand() % 256;
      *vx=random & (opcode & 0xFF);
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
    ++sp;
    stack[sp] = pc;
    pc = (opcode & 0x0FFF);
  }

  void CPU::OP_00EE(){
    //Return back to courotine (like a break)
    pc = stack[sp];
    --sp;
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
    uint8_t shifted = (*VX+VY > 255);
    *VX = (*VX+VY) & 0xFF;
    registers[15]=shifted;
  }

  void CPU::OP_8XY5(){
    //VX =  VX-VY
    uint8_t *VX = &registers[(opcode & 0x0F00) >> 8];
    uint8_t VY = registers[(opcode & 0x00F0) >> 4];
    uint8_t overflow = *VX>=VY;
    std::cout << unsigned(*VX) << ':' << unsigned(VY) << ':' << unsigned(overflow) << '\n';
    *VX = *VX-VY;
    registers[15] = overflow;
  }

  void CPU::OP_8XY7(){
    //VX = VY-VX
    uint8_t *VX = &registers[(opcode & 0x0F00) >> 8];
    uint8_t VY = registers[(opcode & 0x00F0) >> 4];
    uint8_t overflow = VY>=*VX;
    *VX = VY-*VX;
    registers[15] = overflow; 
  }

  void CPU::OP_8XY6(){
    //Set VX to VY and shift VX to the right by 1 bit
    //Set the VF flag to the bit that was shifted out
    uint8_t *VX = &registers[(opcode & 0x0F00) >> 8];
    uint8_t VY = registers[(opcode & 0x00F0) >> 4];
    uint8_t bit_shifted = *VX & 0b1;
    *VX=VY;
    *VX >>= 1;
    registers[15] = bit_shifted; 
  }

  void CPU::OP_8XYE(){
    //Set VX to VY and shift VX to the left by 1 bit
    uint8_t *VX = &registers[(opcode & 0x0F00) >> 8];
    uint8_t VY = registers[(opcode & 0x00F0) >> 4];
    uint8_t bit_shifted = (*VX & 0x80) > 0;
    *VX=VY;
    std::cout << unsigned(VY) << ":";
    *VX <<= 1;
    registers[15] = bit_shifted; 
    std::cout << unsigned(*VX) << " ";
  }

  void CPU::OP_FX07(){
    uint8_t *VX = &registers[(opcode & 0x0F00) >> 8];
    *VX=timer; 
  }

  void CPU::OP_FX15(){
    uint8_t *VX = &registers[(opcode & 0x0F00) >> 8];
    timer=*VX; 
  }

  void CPU::OP_FX18(){
    uint8_t *VX = &registers[(opcode & 0x0F00) >> 8];
    soundtimer=*VX; 
  }

  void CPU::OP_FX1E(){
    uint8_t VX = registers[(opcode & 0x0F00) >> 8];
    index_register+=VX;
  }
  
  void CPU::OP_FX29(){
    uint8_t *VX = &registers[(opcode & 0x0F00) >> 8];
    index_register = 0x50+5*(*VX);
  }

  void CPU::OP_FX33(){
  uint8_t VX = registers[(opcode & 0x0F00) >> 8];
  for(int i =0; i<3; i++){
    memory[index_register+2-i] = VX%10;
    VX=VX/10;
  }    
}

void CPU::OP_FX55(){
  uint8_t VX = (opcode & 0x0F00) >> 8;
  for(int i = 0; i<=VX; i++){
    memory[index_register+i] = registers[i];
  }
}

void CPU::OP_FX65(){
  uint8_t VX = (opcode & 0x0F00) >> 8;
  for(int i = 0; i<=VX; i++){
    registers[i] = memory[index_register+i];
  }
}

void CPU::OP_EX9E(){
  uint8_t VX = registers[(opcode & 0xF00) >> 8];
  std::cout << unsigned(key);
  if (key == VX){
    pc += 2; 
  }
}

void CPU::OP_EXA1(){
  uint8_t VX = registers[(opcode & 0xF00) >> 8];
  std::cout << unsigned(key);
  if (key != VX){
    pc += 2; 
  }
}

void CPU::OP_FX0A(){
  uint8_t *VX = &registers[(opcode & 0xF00) >> 8];
  std::cout << unsigned(key);
 if (key == 0xFF){
  pc -= 2; 
 }
 else{
      *VX=key;
 } 
}

const unsigned int START_ADDRESS = 0x200;
const unsigned int FONTSET_START_ADDRESS = 0x50;

CPU::CPU(const char * filename) {

  romFilename = filename;
  pc = START_ADDRESS;
	memset(video_buffer,0,sizeof(video_buffer));

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
  if (pc > 4096){
    std::cout << "Exceeding size of memory";
  }
  std::cout << '\n' << pc << ": ";
  switch (opcode & 0xF000) {
  case 0x0000:
    switch (opcode & 0xF){
      case 0:
        OP_00E0();
        std::cout << "00E0";
        break;
      case 0xE:
        OP_00EE();
        std::cout << "00EE";
        break;
    }
    break;
  case 0x1000:
    OneNNN();
    std::cout << "1NNN";
    break;
  case 0x2000:
    OP_2NNN();
    std::cout << "2NNN";
    break;
  case 0x3000:
    OP_3XNN();
    std::cout << "3XNN";
    break;
  case 0x4000:
    OP_4XNN();
    std::cout << "4XNN";
    break;
  case 0x5000:
    OP_5XY0();
    std::cout << "5XY0";
    break;
  case 0x6000:
    SIXXNN();
    std::cout << "6XNN";
    break;
  case 0x7000:
    SevenXNN();
    std::cout << "7XNN";
    break;
  case 0x8000:
    switch(opcode & 0x000F){
      case 0:
        OP_8XY0();
        std::cout << "8XY0";
        break;
      case 1:
        OP_8XY1();
        std::cout << "8XY1";
        break;
      case 2:
        OP_8XY2();
        std::cout << "8XY2";
        break;
      case 3:
        OP_8XY3();
        std::cout << "8XY3";
        break;
      case 4:
        OP_8XY4();
        std::cout << "8XY4";
        break;
      case 5:
        OP_8XY5();
        std::cout << "8XY5";
        break;
      case 6:
        OP_8XY6();
        std::cout << "8XY6";
        break;
      case 7:
        OP_8XY7();
        std::cout << "8XY7";
        break;
      case 0xE:
        OP_8XYE();
        std::cout << "8XYE";
        break;
    }
    break;
  case 0x9000:
    OP_9XY0();
    std::cout << "9XY0";
    break;
  case 0xA000:
    ANNN();
    std::cout << "ANNN";
    break;
  case 0xB000:
    OP_BNNN();
    std::cout << "BNNN";
    break;
  case 0xC000:
    OP_CXNN();
    std::cout << "CXNN";
    break;
  case 0xD000:
    DXYN();
    std::cout << "DXYN";
    break;
  case 0xE000:
    switch(opcode & 0x000F){
      case 1:
        OP_EXA1();
        std::cout << "EXA1";
        break;
      case 0xE:
        OP_EX9E();
        std::cout << "EX9E";
        break;
    }
    break;
  case 0xF000:
    switch(opcode & 0xFF){
      case 0x07:
        OP_FX07();
        std::cout << "FX07";
        break;
      case 0x15:
        OP_FX15();
        std::cout << "FX15";
        break;
      case 0x18:
        OP_FX18();
        std::cout << "FX18";
        break;
      case 0x1E:
        OP_FX1E();
        std::cout << "FX1E";
        break;
      case 0x0A:
        OP_FX0A();
        std::cout << "FX0A";
        break;
      case 0x29:
        OP_FX29();
        std::cout << "FX29";
        break;
      case 0x33:
        OP_FX33();
        std::cout << "FX33";
        break;
      case 0x55:
        OP_FX55();
        std::cout << "FX55";
        break;
      case 0x65:
        OP_FX65();
        std::cout << "FX65";
        break;
    }
    break;
  }
  std::cout << '\n';

}
