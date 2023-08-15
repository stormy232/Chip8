#include <stdint.h>
#include <chrono>
#include <random>
#include <string.h>

class CPU{

	public:
		CPU();
		void LoadROM(char const* filename);
		void decode();
		void Cycle();
		void OP_00E0(){
			//clears screen (here we set video buffer to 0)
			memset(video_buffer,0,sizeof(video_buffer));
		}
		void OneNNN(){
			//gets the pc to jump to an address
			uint16_t address = opcode & 0x0FFFu; 
			pc = address;
		}
		void SIXXNN(){
			//sets register vx to a value
			uint8_t value = opcode & 0x00FF;
			uint8_t vx = (opcode & 0x0F00) >> 8;
			registers[vx] = value;
		}
		void SevenXNN(){
			//adds a value to register vx			
			uint8_t value = opcode & 0x00FF;
			uint8_t vx = (opcode & 0x0F00) >> 8;
			registers[vx] += value;
		};
		void ANNN(){
			uint16_t byte3 = opcode & 0x0FFF;
			index_register = byte3;
		};
		void DXYN(){
			uint8_t vx = (opcode & 0x0F00) >> 8;
			uint8_t vy = (opcode & 0x00F0) >> 4;
			uint8_t height = (opcode & 0x000F);

			uint8_t x_pos = registers[vx] % MAX_HEIGHT;
			uint8_t y_pos = registers[vy] % MAX_WIDTH;

			registers[15] = 0;

			for(int row=0; row<height; ++row){
			
			}
		};

		uint8_t fontset[80] = {
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

		private:
			const uint8_t MAX_WIDTH = 64;
			const uint8_t MAX_HEIGHT = 32;

			std::uniform_int_distribution<uint8_t> randByte;
			//input keys and display memory
			uint8_t input[16]{};
			uint32_t video_buffer[64*32];
			
			/*registers,memory,stack,stack_pointer,program_counter
				delaytimer,soundtimer,opcodes			*/
			
			uint8_t registers[16];
			uint8_t memory[4096];
			uint16_t index_register;
			uint16_t pc;
			uint16_t stack[16];
			uint8_t sp;
			uint8_t timer;
			uint8_t soundtimer;
			uint16_t opcode;

};




