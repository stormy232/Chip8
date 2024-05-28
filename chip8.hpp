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
		void OP_00E0();
		void OneNNN();
		void SIXXNN();
		void SevenXNN();
		void ANNN();
		void DXYN();
			


		uint8_t fontset[80];  

	
			const uint8_t MAX_WIDTH = 64;
			const uint8_t MAX_HEIGHT = 32;

			std::uniform_int_distribution<uint8_t> randByte;
			//input keys and display memory
			uint8_t input[16]{};
			uint32_t video_buffer[64*32];
			
			/*registers,memory,stack,stack_pointer,program_counter
				delaytimer,soundtimer,opcodes			*/
	private:		
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




