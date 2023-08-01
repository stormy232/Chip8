#include <stdint.h>

class CPU{

	public:

		void LoadROM(char const* filename);


		//input keys and display memory
		uint8_t input[16]{};
		uint32_t video_buffer[64*32];
		/*registers,memory,stack,stack_pointer,program_counter
			delaytimer,soundtimer,opcodes			*/
		uint8_t registers[16]{};
		uint8_t memory[4096]{};
		uint16_t index_register{};
		uint16_t pc{};
		uint16_t stack[16]{};
		uint8_t sp{};
		uint8_t timer{};
		uint8_t soundtimer{};
		uint16_t opcode{};
}




